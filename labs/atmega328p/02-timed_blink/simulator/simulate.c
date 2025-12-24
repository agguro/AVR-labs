// labs/atmega328p/01-blink/simulator/simulate.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "/tmp/simavr_gpio.sock"
#define RED_LED   "\033[31m●\033[0m"
#define OFF_LED   "○"

/**
 * Updates the terminal line with the current LED status.
 * Uses carriage return (\r) to overwrite the same line.
 */
void print_status(const char* led_icon, const char* status_text) {
    // Trailing spaces ensure we clear any leftover characters from previous strings
    printf("\r[%s] PB5 (Built-in LED) %s    ", status_text, led_icon);
    fflush(stdout);
}

int main() {
    struct sockaddr_un addr;
    char buffer[4096]; // Large buffer to handle high-frequency data bursts

    while (1) {
        int sock = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&addr, 0, sizeof(addr));
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);

        print_status(OFF_LED, "WAITING");

        // Attempt to connect to the simavr host
        while (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
            sleep(1);
        }

        print_status(OFF_LED, "CONNECTED");

        ssize_t n;
        // Read incoming GPIO state changes from the Unix socket
        while ((n = read(sock, buffer, sizeof(buffer) - 1)) > 0) {
            buffer[n] = '\0';
            
            // Process EVERY line in the buffer (crucial for high-speed signals)
            char *line = strtok(buffer, "\n");
            while (line != NULL) {
                // The protocol sends: "E <index> <pin_name> <value>"
                // We look for the last space to extract the value (0 or 1)
                char *last_space = strrchr(line, ' ');
                if (last_space) {
                    int val = atoi(last_space + 1);
                    print_status(val ? RED_LED : OFF_LED, "ACTIVE");
                }
                line = strtok(NULL, "\n");
            }
        }

        // Connection lost or closed
        close(sock);
    }

    return 0;
}
