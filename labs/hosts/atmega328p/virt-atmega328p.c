//labs/hosts/atmega328p/virt-atmega328p.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>
#include <termios.h>
#include <fcntl.h>

#include <simavr/sim_avr.h>
#include <simavr/sim_elf.h>
#include <simavr/avr_ioport.h>

#define SOCK_PATH "/tmp/simavr_gpio.sock"

static int client_fd = -1;
static pthread_mutex_t client_lock = PTHREAD_MUTEX_INITIALIZER;

// --- Socket Callbacks for GPIO ---
void pb5_changed_hook(struct avr_irq_t *irq, uint32_t value, void *param) {
    char buf[64];
    // Format: Event [index] [pin_name] [state]
    int len = snprintf(buf, sizeof(buf), "E 0 PORTB 5 %u\n", value ? 1 : 0);
    
    pthread_mutex_lock(&client_lock);
    if (client_fd >= 0) {
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

// --- Main Simulator with Lockdown Sync ---
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <firmware.elf>\n", argv[0]);
        return 1;
    }

    // Initialize IPC Socket
    int listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr = { .sun_family = AF_UNIX };
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path)-1);
    unlink(SOCK_PATH);
    bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(listen_fd, 1);
    
    pthread_t tid;
    pthread_create(&tid, NULL, socket_accept_thread, (void*)(intptr_t)listen_fd);

    // Initialize MCU
    avr_t *avr = avr_make_mcu_by_name("atmega328p");
    if (!avr) return 1;
    avr_init(avr);
    
    // Set Target Frequency (Adjustable via + and - keys)
    avr->frequency = 16000000; 

    // Load Firmware
    elf_firmware_t fw;
    memset(&fw, 0, sizeof(fw));
    if (elf_read_firmware(argv[1], &fw) != 0) {
        fprintf(stderr, "Error: Could not read ELF file %s\n", argv[1]);
        return 1;
    }
    avr_load_firmware(avr, &fw);
    
    // Register GPIO hooks (PORTB Pin 5 / Built-in LED)
    avr_irq_t *pb5_irq = avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ('B'), 5);
    
    avr_irq_register_notify(pb5_irq, pb5_changed_hook, NULL);

    // Timing state
    struct timespec start_time, current_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    
    uint64_t last_report_cycle = 0;
    struct timespec last_report_time = start_time;

    while (1) {
        // Run a batch of instructions
        for (int i = 0; i < 5000; i++) avr_run(avr);

        // Calculate Real Time Elapsed
        clock_gettime(CLOCK_MONOTONIC, &current_time);
        double real_elapsed = (current_time.tv_sec - start_time.tv_sec) + 
                             (current_time.tv_nsec - start_time.tv_nsec) / 1e9;
        
        // Calculate Simulated Time Elapsed
        double sim_elapsed = (double)avr->cycle / avr->frequency;

        // Sync Logic: If simulation is ahead of real time, wait
        if (sim_elapsed > real_elapsed) {
            double wait_us = (sim_elapsed - real_elapsed) * 1000000.0;
            if (wait_us > 100) usleep((useconds_t)wait_us);
        }

        // Periodic Status Report (Every 1 second)
        double interval = (current_time.tv_sec - last_report_time.tv_sec) + 
                         (current_time.tv_nsec - last_report_time.tv_nsec) / 1e9;

        if (interval >= 1.0) {
            double current_mips = (avr->cycle - last_report_cycle) / interval / 1e6;

            printf("\r[STATUS] Real-Time: %.1fs | Sim Performance: %.2f MHz | Target: %.2f MHz    ", 
                   real_elapsed, current_mips, avr->frequency / 1e6);
            fflush(stdout);

            last_report_cycle = avr->cycle;
            last_report_time = current_time;
        }

    }
    
    printf("\nSimulation finished.\n");
    return 0;
}
