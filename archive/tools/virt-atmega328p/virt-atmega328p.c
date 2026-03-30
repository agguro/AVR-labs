#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>

#include <simavr/sim_avr.h>
#include <simavr/sim_elf.h>
#include <simavr/avr_ioport.h>

static int client_fd = -1;
static pthread_mutex_t client_lock = PTHREAD_MUTEX_INITIALIZER;

// --- Socket Callbacks for GPIO ---
void pb5_changed_hook(struct avr_irq_t *irq, uint32_t value, void *param) {
    char buf[64];
    // This matches the protocol simulate.c expects
    int len = snprintf(buf, sizeof(buf), "E 0 PB5 %u\n", value ? 1 : 0);
    
    pthread_mutex_lock(&client_lock);
    if (client_fd >= 0) {
        // MSG_NOSIGNAL prevents the program from crashing if simulate.c closes
        send(client_fd, buf, len, MSG_NOSIGNAL);
    }
    pthread_mutex_unlock(&client_lock);
}

void *socket_accept_thread(void *arg) {
    int listen_fd = (intptr_t)arg;
    while (1) {
        int fd = accept(listen_fd, NULL, NULL);
        if (fd >= 0) {
            pthread_mutex_lock(&client_lock);
            if (client_fd >= 0) close(client_fd);
            client_fd = fd;
            pthread_mutex_unlock(&client_lock);
        }
    }
    return NULL;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <firmware.elf> [socket_path]\n", argv[0]);
        return 1;
    }

    // Dynamic Socket Path: Use argument if provided, otherwise default
    const char *sock_path = (argc > 2) ? argv[2] : "/tmp/simavr_gpio.sock";

    // Initialize IPC Socket Server
    int listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr = { .sun_family = AF_UNIX };
    strncpy(addr.sun_path, sock_path, sizeof(addr.sun_path)-1);
    
    unlink(sock_path); // Clean up previous socket file
    if (bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return 1;
    }
    listen(listen_fd, 1);
    
    pthread_t tid;
    pthread_create(&tid, NULL, socket_accept_thread, (void*)(intptr_t)listen_fd);

    // Initialize MCU
    avr_t *avr = avr_make_mcu_by_name("atmega328p");
    if (!avr) return 1;
    avr_init(avr);
    avr->frequency = 16000000; 

    // Load Firmware
    elf_firmware_t fw;
    memset(&fw, 0, sizeof(fw));
    if (elf_read_firmware(argv[1], &fw) != 0) {
        fprintf(stderr, "Error: Could not read ELF file %s\n", argv[1]);
        return 1;
    }
    avr_load_firmware(avr, &fw);
    
    // Register GPIO hooks for PB5
    avr_irq_t *pb5_irq = avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ('B'), 5);
    avr_irq_register_notify(pb5_irq, pb5_changed_hook, NULL);

    printf("[MCU] Virtual ATmega328P running on %s\n", sock_path);

    // Timing and Sync State
    struct timespec start_time, current_time, last_report_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    last_report_time = start_time;
    uint64_t last_report_cycle = 0;

    while (1) {
        // Run a batch of instructions
        for (int i = 0; i < 5000; i++) avr_run(avr);

        clock_gettime(CLOCK_MONOTONIC, &current_time);
        
        // Time calculations
        double real_elapsed = (current_time.tv_sec - start_time.tv_sec) + 
                             (current_time.tv_nsec - start_time.tv_nsec) / 1e9;
        double sim_elapsed = (double)avr->cycle / avr->frequency;

        // Sync: Keep simulation from running too fast
        if (sim_elapsed > real_elapsed) {
            double wait_us = (sim_elapsed - real_elapsed) * 1000000.0;
            if (wait_us > 100) usleep((useconds_t)wait_us);
        }

        // Status Report
        double interval = (current_time.tv_sec - last_report_time.tv_sec) + 
                         (current_time.tv_nsec - last_report_time.tv_nsec) / 1e9;

        if (interval >= 1.0) {
            double current_mhz = (avr->cycle - last_report_cycle) / interval / 1e6;
            printf("\r[STATUS] Real: %.1fs | Sim: %.2f MHz | Target: 16.00 MHz    ", 
                   real_elapsed, current_mhz);
            fflush(stdout);

            last_report_cycle = avr->cycle;
            last_report_time = current_time;
        }
    }

    return 0;
}
