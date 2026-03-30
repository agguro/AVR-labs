#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glob.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>

typedef struct {
    const char *mcu_alias;
    const char *avrdude_mcu;
    const char *protocol;
    const char *default_baud;
    int needs_1200_reset;
} AVRConfig;

static const AVRConfig configs[] = {
    {"uno",       "m328p", "arduino", "115200", 0},
    {"nano",      "m328p", "arduino", "57600",  0},
    {"pro-mini",  "m328p", "arduino", "57600",  0},
    {"leonardo",  "m32u4", "avr109",  "57600",  1},
    {"attiny85",  "t85",   "usbasp",  NULL,     0},
    {NULL, NULL, NULL, NULL, 0}
};

static int is_verbose = 0;
static int is_recovery = 0;

static int run_avrdude(char *const argv[]) {
    pid_t pid = fork();
    if (pid == 0) {
        if (!is_verbose) {
            int devnull = open("/dev/null", O_WRONLY);
            dup2(devnull, STDERR_FILENO);
            close(devnull);
        }
        execvp("avrdude", argv);
        perror("execvp");
        _exit(1);
    }
    int status;
    waitpid(pid, &status, 0);
    return WIFEXITED(status) && WEXITSTATUS(status) == 0;
}

static char *detect_port(void) {
    static char port[128];
    glob_t g;
    const char *pattern = "/dev/{ttyACM*,ttyUSB*,tty.usbserial*,cu.usbmodem*}";
    if (glob(pattern, GLOB_BRACE, NULL, &g) == 0 && g.gl_pathc > 0) {
        strncpy(port, g.gl_pathv[0], sizeof(port));
        globfree(&g);
        return port;
    }
    return NULL;
}

static void trigger_1200_reset(const char *port) {
    if (is_verbose) printf("[DEBUG] Opening %s at 1200 baud for reset...\n", port);
    int fd = open(port, O_RDWR | O_NOCTTY);
    if (fd >= 0) {
        struct termios settings;
        tcgetattr(fd, &settings);
        cfsetispeed(&settings, B1200);
        cfsetospeed(&settings, B1200);
        tcsetattr(fd, TCSANOW, &settings);
        usleep(100000); 
        close(fd);
        usleep(500000); 
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-v] [-r] <firmware.hex> [mcu_alias]\n", argv[0]);
        fprintf(stderr, "Options:\n  -v : Verbose (Full Report)\n  -r : Recover (Read from chip to file)\n");
        return 1;
    }

    const char *hex = NULL;
    const char *user_mcu = "uno";
    
    // Improved argument parsing
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            is_verbose = 1;
        } else if (strcmp(argv[i], "-r") == 0) {
            is_recovery = 1;
        } else if (hex == NULL) {
            hex = argv[i];
        } else {
            user_mcu = argv[i];
        }
    }

    if (!hex) {
        fprintf(stderr, "Error: No hex file specified.\n");
        return 1;
    }

    char *port = detect_port();
    if (!port) {
        fprintf(stderr, "Error: No device found.\n");
        return 1;
    }

    const char *protocol = "arduino";
    const char *mcu_type = user_mcu;
    const char *selected_baud = NULL;
    int needs_reset = 0;

    for (int i = 0; configs[i].mcu_alias; i++) {
        if (strcmp(user_mcu, configs[i].mcu_alias) == 0 || strcmp(user_mcu, configs[i].avrdude_mcu) == 0) {
            mcu_type = configs[i].avrdude_mcu;
            protocol = configs[i].protocol;
            selected_baud = configs[i].default_baud;
            needs_reset = configs[i].needs_1200_reset;
            break;
        }
    }

    if (needs_reset) trigger_1200_reset(port);

    // Probing only makes sense for the 'arduino' protocol (Uno/Nano)
    if (selected_baud && strcmp(protocol, "arduino") == 0) {
        const char *bauds[] = {selected_baud, "115200", "57600", "19200", NULL};
        int found = 0;
        for (int i = 0; bauds[i]; i++) {
            if (is_verbose) printf("[PROBE] Testing %s baud...\n", bauds[i]);
            char *probe[] = {"avrdude", "-c", (char*)protocol, "-p", (char*)mcu_type, "-P", port, "-b", (char*)bauds[i], "-n", "-q", NULL};
            if (run_avrdude(probe)) {
                selected_baud = bauds[i];
                found = 1;
                break;
            }
        }
        if (!found) {
            fprintf(stderr, "Error: Could not sync with %s. Try -v for details.\n", user_mcu);
            return 1;
        }
    }

    // Prepare the command
    char flash_arg[256];
    if (is_recovery) {
        printf("[RECOVERY] Reading from %s (%s) to %s...\n", mcu_type, port, hex);
        snprintf(flash_arg, sizeof(flash_arg), "flash:r:%s:i", hex);
    } else {
        printf("[FLASH] Writing %s to %s (%s)...\n", hex, mcu_type, port);
        snprintf(flash_arg, sizeof(flash_arg), "flash:w:%s:i", hex);
    }

    char *args[20];
    int n = 0;
    args[n++] = "avrdude";
    if (is_verbose) args[n++] = "-v";
    args[n++] = "-c"; args[n++] = (char*)protocol;
    args[n++] = "-p"; args[n++] = (char*)mcu_type;
    args[n++] = "-P"; args[n++] = port;
    if (selected_baud) {
        args[n++] = "-b"; args[n++] = (char*)selected_baud;
    }
    if (!is_recovery) args[n++] = "-D"; // Disable auto-erase only when writing
    args[n++] = "-U"; args[n++] = flash_arg;
    args[n++] = NULL;

    if (run_avrdude(args)) {
        printf("\n[SUCCESS] Operation completed.\n");
        return 0;
    } else {
        printf("\n[FAILURE] Operation failed.\n");
        return 1;
    }
}
