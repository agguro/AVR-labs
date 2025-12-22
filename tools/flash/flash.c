//labs/tools/flash/flash.c

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glob.h>
#include <sys/wait.h>

static const char *baudrates[] = {
    "115200", // Standard for Arduino Uno
    "57600",  // Standard for Arduino Nano/Pro Mini
    "19200",  // Older bootloaders
    NULL
};

static int run_avrdude(char *const argv[]) {
    pid_t pid = fork();
    if (pid == 0) {
        execvp("avrdude", argv);
        perror("exec avrdude");
        _exit(1);
    }

    int status;
    waitpid(pid, &status, 0);
    return WIFEXITED(status) && WEXITSTATUS(status) == 0;
}

static char *detect_port(void) {
    static char port[128];
    glob_t g;

    // Check for Arduino-style ports (ACM) or USB-serial clones (USB)
    if (glob("/dev/ttyACM*", 0, NULL, &g) == 0 && g.gl_pathc > 0) {
        strncpy(port, g.gl_pathv[0], sizeof(port));
        globfree(&g);
        return port;
    }

    if (glob("/dev/ttyUSB*", 0, NULL, &g) == 0 && g.gl_pathc > 0) {
        strncpy(port, g.gl_pathv[0], sizeof(port));
        globfree(&g);
        return port;
    }

    return NULL;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <firmware.hex> [mcu_type]\n", argv[0]);
        return 1;
    }

    const char *hex = argv[1];
    // Default to m328p, but allow overrides for ATtiny or other ATmegas
    const char *mcu = (argc > 2) ? argv[2] : "m328p";
    const char *prog = "arduino";

    char *port = detect_port();
    if (!port) {
        fprintf(stderr, "Error: No Arduino serial port found.\n");
        return 1;
    }

    printf("Detected port: %s\n", port);

    const char *baud = NULL;
    for (int i = 0; baudrates[i]; i++) {
        printf("Probing baudrate %s for %s...\n", baudrates[i], mcu);

        char *probe[] = {
            "avrdude",
            "-c", (char *)prog,
            "-P", port,
            "-b", (char *)baudrates[i],
            "-p", (char *)mcu,
            "-n", // no-write (probe only)
            NULL
        };

        if (run_avrdude(probe)) {
            baud = baudrates[i];
            printf("✓ Success: Programmer responded at %s baud\n", baud);
            break;
        }
    }

    if (!baud) {
        fprintf(stderr, "Error: Could not detect baudrate. Check your connections.\n");
        return 1;
    }

    printf("Flashing %s to %s...\n", hex, mcu);

    char uf[256];
    snprintf(uf, sizeof(uf), "flash:w:%s:i", hex);

    char *flash[] = {
        "avrdude",
        "-c", (char *)prog,
        "-P", port,
        "-b", (char *)baud,
        "-p", (char *)mcu,
        "-D", // Keep EEPROM
        "-U", uf,
        NULL
    };

    return run_avrdude(flash) ? 0 : 1;
}
