Project Overview: Mastering the ATmega328P

File: Project_Notes.txt
1. The Assembly Logic (Timed Blink)

We replaced the standard Arduino C++ abstraction with raw Assembly to gain precision and minimize overhead.

    Goal: Blink the built-in LED (PB5 / Digital Pin 13) every 1 second using an interrupt, allowing the main_loop to remain empty.

    The Timer: We used Timer/Counter 1 (16-bit).

        Mode: CTC (Clear Timer on Compare Match). The hardware automatically resets the counter to zero when it hits the target value.

        Math: At a 16MHz clock speed with a 1024 prescaler, the timer ticks 15,625 times per second (16,000,000/1024).

        Compare Value: We set OCR1A to 15624 (0 to 15624 = 15,625 counts).

    The Toggle Trick: Instead of reading the state of the pin and flipping it, we wrote a 1 to the PINB register (Address 0x03). In AVR architecture, writing a 1 to a PIN register bit toggles the corresponding PORT register bit instantly.

2. Critical Lessons Learned

Through our troubleshooting, we identified several "gotchas" that often trip up assembly programmers:

    Register Addresses (0x80 vs 0xA0): While some chips use 0xA0 for Timer1, the ATmega328P uses 0x80. Using the wrong address means the CPU is writing data into "empty air," and the timer never starts.

    Interrupt Vector Table (IVT): The hardware expects the "Jump" to the Timer ISR to be at a specific byte address. For the 328P, Timer1 Compare Match A is at 0x0022. If this is misaligned, the interrupt will trigger, but the CPU will jump into the wrong code and likely crash.

    Stack Discipline: The Stack Pointer (SP) must be initialized to the end of RAM (0x08FF). Furthermore, for every push in an ISR, there must be a corresponding pop. If the stack is unbalanced, the reti instruction will grab a "return address" that is actually your saved data, causing a "stack smash" and restart.

    Bootloader Safety: Flashing via the USB cable uses the existing bootloader. This means the bootloader section at the "high" end of memory is safe, while your assembly code occupies the "application" section starting at 0x0000.
