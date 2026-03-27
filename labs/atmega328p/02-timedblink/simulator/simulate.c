#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// ANSI-kleuren voor een stoere terminal look
#define BIG_LED_ON  "\033[1;33m  ██  \033[0m" // Felgeel blok
#define BIG_LED_OFF "\033[1;30m  ░░  \033[0m" // Donkergrijs blok
#define CLR_LINE    "\r\033[K"             // Regel wissen en cursor naar begin

void print_status(const char* led_icon, const char* status_text) {
    printf("%s[ %-10s ]  LED PIN 13: %s", CLR_LINE, status_text, led_icon);
    fflush(stdout);
}

int main() {
    int server_fd, client_sock;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024];

    // 1. Maak socket (TCP)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket mislukt");
        exit(EXIT_FAILURE);
    }

    // 2. Voorkom "Address already in use" errors
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(9999); // Dezelfde poort als de bridge verwacht

    // 3. Bind aan de poort
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind mislukt. Draait server.py nog?");
        exit(EXIT_FAILURE);
    }

    // 4. Luisteren naar binnenkomende bridge-verbindingen
    if (listen(server_fd, 3) < 0) {
        perror("Listen mislukt");
        exit(EXIT_FAILURE);
    }

    printf("--- Direct Bridge Monitor ---\n");
    printf("Wachten op verbinding van ./bridge op poort 9999...\n");

    while (1) {
        print_status(BIG_LED_OFF, "WAITING");
        
        if ((client_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept mislukt");
            continue;
        }

        print_status(BIG_LED_OFF, "CONNECTED");

        ssize_t n;
        while ((n = recv(client_sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
            buffer[n] = '\0';
            
            // Check het laatste karakter voor de status
            char state = buffer[n-1];
            
            if (state == '1') {
                print_status(BIG_LED_ON, "ACTIVE");
            } else if (state == '0') {
                print_status(BIG_LED_OFF, "ACTIVE");
            }
        }

        close(client_sock);
        printf("\nBridge verbinding verloren. Opnieuw wachten...\n");
    }

    return 0;
}
