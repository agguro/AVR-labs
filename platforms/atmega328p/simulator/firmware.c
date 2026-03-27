#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= (1 << 5); // PB5 output

    while (1) {
        PORTB ^= (1 << 5); // toggle LED
        _delay_ms(1000);
    }
}
