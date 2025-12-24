#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

// Using larger/bolder ANSI symbols
#define BIG_LED_ON  "\033[1;31m  ██████  \033[0m" // Bold Red Block
#define BIG_LED_OFF "\033[1;30m  ░░░░░░  \033[0m" // Dim Gray Block

void print_status(const char* led_icon, const char* status_text) {
    // Clear line and print high-visibility status
    printf("\r\033[K[ %-10s ]  LED STATE: %s", status_text, led_icon);
    fflush(stdout);
}

int main(int argc, char *argv[]) {
    struct sockaddr_un addr;
    char buffer[4096];
    
    // Get socket path from argument or use default
    const char *sock_path = (argc > 1) ? argv[1] : "/tmp/simavr_gpio.sock";

    while (1) {
        int sock = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&addr, 0, sizeof(addr));
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, sock_path, sizeof(addr.sun_path) - 1);

        print_status(BIG_LED_OFF, "WAITING");

        // Attempt to connect
        while (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
            sleep(1);
        }

        print_status(BIG_LED_OFF, "CONNECTED");

        ssize_t n;
        while ((n = read(sock, buffer, sizeof(buffer) - 1)) > 0) {
            buffer[n] = '\0';
            
            char *line = strtok(buffer, "\n");
            while (line != NULL) {
                // Look for "PB5" in the event string from virt-atmega328p
                if (strstr(line, "PB5")) {
                    char *last_space = strrchr(line, ' ');
                    if (last_space) {
                        int val = atoi(last_space + 1);
                        print_status(val ? BIG_LED_ON : BIG_LED_OFF, "ACTIVE");
                    }
                }
                line = strtok(NULL, "\n");
            }
        }
        close(sock);
    }
    return 0;
}
