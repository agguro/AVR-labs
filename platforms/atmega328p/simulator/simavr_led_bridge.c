#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>

#include <simavr/sim_avr.h>
#include <simavr/sim_elf.h>
#include <simavr/avr_ioport.h>

/* Global variables for networking */
int server_fd = 0;
int client_sock = -1;

/* * Callback triggered whenever the monitored AVR pin changes state.
 * It sends '1' for HIGH and '0' for LOW to the connected client.
 */
static void pin_changed_callback(struct avr_irq_t *irq, uint32_t value, void *param) {
    (void)irq; 
    (void)param;

    if (client_sock != -1) {
        char state = value ? '1' : '0';
        /* MSG_NOSIGNAL prevents the program from crashing if the client disconnects abruptly */
        if (send(client_sock, &state, 1, MSG_NOSIGNAL) < 0) {
            printf("\n[Bridge] Client connection lost.\n");
            close(client_sock);
            client_sock = -1;
        }
    }
}

int main(int argc, char *argv[]) {
    /* 1. Argument validation */
    if (argc < 6) {
        fprintf(stderr, "Usage: %s <firmware.elf> <mcu> <tcp_port> <io_port_letter> <pin_number>\n", argv[0]);
        fprintf(stderr, "Example (Uno Pin 13): %s blink.elf atmega328p 9999 B 5\n", argv[0]);
        fprintf(stderr, "Example (ATtiny85 PB0): %s tiny.elf attiny85 9998 B 0\n", argv[0]);
        return 1;
    }

    const char *firmware_path = argv[1];
    const char *mcu_name = argv[2];
    int tcp_port = atoi(argv[3]);
    char port_letter = argv[4][0];
    int pin_number = atoi(argv[5]);

    /* 2. Initialize the SimAVR core */
    avr_t *avr = avr_make_mcu_by_name(mcu_name);
    if (!avr) {
        fprintf(stderr, "Error: MCU '%s' not supported by simavr.\n", mcu_name);
        return 1;
    }
    avr_init(avr);

    /* 3. Load the firmware */
    elf_firmware_t fw;
    memset(&fw, 0, sizeof(fw));
    if (elf_read_firmware(firmware_path, &fw) != 0) {
        fprintf(stderr, "Error: Could not load firmware '%s'\n", firmware_path);
        return 1;
    }
    avr_load_firmware(avr, &fw);
    printf("[Bridge] Loaded '%s' onto %s\n", firmware_path, mcu_name);

    /* 4. Setup TCP Server Socket */
    struct sockaddr_in address;
    int opt = 1;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    /* Set server socket to non-blocking mode to keep simulation running without waiting for clients */
    fcntl(server_fd, F_SETFL, O_NONBLOCK);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(tcp_port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Socket bind failed");
        return 1;
    }
    listen(server_fd, 1);

    /* 5. Attach IRQ to the specified Pin */
    avr_irq_t *pin_irq = avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ(port_letter), pin_number);
    if (pin_irq) {
        avr_irq_register_notify(pin_irq, pin_changed_callback, NULL);
        printf("[Bridge] Monitoring Port %c Pin %d\n", port_letter, pin_number);
    } else {
        fprintf(stderr, "Error: Could not find Port %c Pin %d on %s\n", port_letter, pin_number, mcu_name);
        return 1;
    }

    printf("[Bridge] Server listening on port %d...\n", tcp_port);

    /* 6. Main Simulation Loop */
    uint32_t network_check_counter = 0;
    while (1) {
        /* Run one AVR instruction cycle */
        avr_run(avr);

        /* Periodically check for new incoming monitor connections (every 10k cycles) */
        if (++network_check_counter > 10000) {
            network_check_counter = 0;
            if (client_sock == -1) {
                int new_sock = accept(server_fd, NULL, NULL);
                if (new_sock >= 0) {
                    printf("[Bridge] New client connected on port %d!\n", tcp_port);
                    client_sock = new_sock;
                    /* Set client socket to non-blocking for maximum performance */
                    fcntl(client_sock, F_SETFL, O_NONBLOCK);
                }
            }
        }
    }

    return 0;
}
