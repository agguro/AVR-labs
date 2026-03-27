#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>

#include "sim_avr.h"
#include "sim_elf.h"
#include "avr_ioport.h"
#include "avr_adc.h"

#define SOCKET_PATH "/tmp/attiny85.sock"
#define VCC_MV 5000
#define REPORT_INTERVAL_CYCLES 10000 // Report PWM every 10ms at 1MHz

typedef struct {
    uint8_t mcu_dir;          // 0=In, 1=Out (DDRB)
    uint8_t mcu_pin_val;      // Binary state (0/1)
    uint32_t ext_voltage_mv;  // Voltage driven from outside world
    
    // Virtual Voltmeter (PWM Integration)
    uint64_t last_cycle;
    uint64_t high_cycles;
    uint64_t total_cycles;
    uint32_t last_reported_mv;
} pin_state_t;

pin_state_t pins[6]; // PB0 through PB5
avr_t * avr = NULL;
int server_fd, client_fd = -1;

// --- Helper: Send Voltage to Socket ---
void report_voltage(int pin_idx, uint32_t mv) {
    if (client_fd != -1 && mv != pins[pin_idx].last_reported_mv) {
        char buf[32];
        int n = snprintf(buf, sizeof(buf), "PB%d:%u\n", pin_idx, mv);
        send(client_fd, buf, n, 0);
        pins[pin_idx].last_reported_mv = mv;
    }
}

// --- Callback: Pin Logic Level Changed ---
void on_pin_value(struct avr_irq_t *irq, uint32_t val, void *param) {
    int i = (intptr_t)param;
    uint64_t now = avr->cycle;
    uint64_t delta = now - pins[i].last_cycle;

    // 1. Accumulate Energy for PWM smoothing
    if (pins[i].mcu_pin_val == 1) {
        pins[i].high_cycles += delta;
    }
    pins[i].total_cycles += delta;

    // 2. Immediate Digital Reporting (0V or 5000V)
    if (val != pins[i].mcu_pin_val) {
        report_voltage(i, val ? VCC_MV : 0);
    }

    pins[i].mcu_pin_val = val;
    pins[i].last_cycle = now;

    // 3. PWM Quantization Logic (8-bit Hardware Accuracy)
    if (pins[i].total_cycles >= REPORT_INTERVAL_CYCLES) {
        // Calculate the 8-bit step (0-255)
        uint32_t step = (uint32_t)((pins[i].high_cycles * 255ULL) / pins[i].total_cycles);
        // Convert to Hardware Millivolts (e.g. 2509mV)
        uint32_t hardware_mv = (step * VCC_MV) / 255;

        // Only report if it's "Analog" (not a solid 0V or 5000V)
        if (hardware_mv > 50 && hardware_mv < 4950) {
            report_voltage(i, hardware_mv);
        }

        pins[i].high_cycles = 0;
        pins[i].total_cycles = 0;
    }
}

// --- Callback: Pin Direction (DDR) Changed ---
void on_pin_dir(struct avr_irq_t *irq, uint32_t val, void *param) {
    int i = (intptr_t)param;
    pins[i].mcu_dir = val;
    printf("[SIM] PB%d set to %s\n", i, val ? "OUTPUT" : "INPUT");
}

// --- Socket Communication Parser ---
void handle_external_input() {
    char buf[64];
    ssize_t n = recv(client_fd, buf, sizeof(buf)-1, 0);
    if (n <= 0) {
        if (n == 0 || (n < 0 && errno != EAGAIN)) {
            close(client_fd); client_fd = -1;
            printf("[SIM] Controller disconnected.\n");
        }
        return;
    }
    buf[n] = '\0';

    int idx, mv_in;
    // Protocol: "PB0:5000" (Digital) or "A1:2500" (Analog ADC)
    if (sscanf(buf, "PB%d:%d", &idx, &mv_in) == 2 && idx <= 5) {
        uint8_t logic = (mv_in > 2500) ? 1 : 0; // Standard CMOS threshold
        pins[idx].ext_voltage_mv = mv_in;

        // Check for Electrical Contention (Short Circuit)
        if (pins[idx].mcu_dir == 1 && pins[idx].mcu_pin_val != logic) {
            fprintf(stderr, "🚨 CONTENTION! PB%d | MCU drives %dmV | External drives %dmV\n", 
                    idx, pins[idx].mcu_pin_val ? 5000 : 0, mv_in);
        }

        avr_raise_irq(avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ('B'), idx), logic);
    } 
    else if (sscanf(buf, "A%d:%d", &idx, &mv_in) == 2) {
        // Direct injection into ADC Channels (0-3)
        avr_irq_t * adc_irq = avr_io_getirq(avr, AVR_IOCTL_ADC_GETIRQ, idx);
        if (adc_irq) avr_raise_irq(adc_irq, (uint32_t)mv_in);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <firmware.elf>\n", argv[0]);
        return 1;
    }

    elf_firmware_t f;
    if (elf_read_firmware(argv[1], &f) != 0) return 1;

    avr = avr_make_mcu_by_name("attiny85");
    if (!avr) return 1;
    avr_init(avr);
    avr_load_firmware(avr, &f);

    // Attach Hooks to PB0..PB5
    for (int i = 0; i < 6; i++) {
        avr_irq_register_handler(avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ('B'), i), on_pin_value, (void*)(intptr_t)i);
        avr_irq_register_handler(avr_io_getirq(avr, AVR_IOCTL_IOPORT_GETIRQ_DIRECTION('B'), i), on_pin_dir, (void*)(intptr_t)i);
    }

    // Unix Socket Setup
    unlink(SOCKET_PATH);
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    fcntl(server_fd, F_SETFL, fcntl(server_fd, F_GETFL, 0) | O_NONBLOCK);
    struct sockaddr_un addr = { .sun_family = AF_UNIX };
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path)-1);
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);

    printf("--- ATtiny85 Pure-Integer Simulator Active ---\n");

    while (1) {
        // Run simulation
        int state = avr_run(avr);
        if (state == cpu_Done || state == cpu_Crashed) break;

        // Handle Socket
        if (client_fd == -1) {
            client_fd = accept(server_fd, NULL, NULL);
            if (client_fd != -1) {
                fcntl(client_fd, F_SETFL, fcntl(client_fd, F_GETFL, 0) | O_NONBLOCK);
                printf("[SIM] Controller connected.\n");
            }
        } else {
            handle_external_input();
        }
    }
    return 0;
}

