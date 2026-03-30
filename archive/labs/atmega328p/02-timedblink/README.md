# Lab 02: Timed Blink (Hardware Timers & Interrupts)

This lab moves beyond software-based delay loops to explore the precise world of hardware-timed execution. You will configure the ATmega328P's 16-bit Timer1 to handle the blink timing independently of the main execution thread.

## Hardware Setup

While the Arduino has a built-in LED on Pin 13, you can connect an external LED for better visibility:

1. **LED Anode (Long Leg)**: Connect to **Digital Pin 13**.
2. **Resistor (220Ω)**: Connect one end to the **LED Cathode (Short Leg)** and the other to **GND**.
3. **Resistor Color Code**: Red-Red-Brown (indicates 220 ohms).

*Note: The ATmega328P bit for this pin is **PB5** (Bit 5 of Port B).*

## Workflow

1. **Precision Timing**: Calculating the exact OCR1A values for a 1Hz blink at a 16MHz clock speed.
2. **CTC Mode Setup**: Configuring the "Clear Timer on Compare Match" mode to automate the timing cycle.
3. **Interrupt Handling**: Implementing an Interrupt Service Routine (ISR) to toggle the LED, allowing the main loop to remain idle.
4. **Logic Verification**: Using the simulator to ensure the interrupt triggers at the correct cycle count.

---

## How the Program Works

This lab utilizes the **16-bit Timer/Counter 1**:
* **Prescaler**: Set to 1024, reducing the 16MHz clock to 15,625 ticks per second.
* **OCR1A (Output Compare Register A)**: Set to 7,811 ($0x1E83$) to trigger an interrupt every 0.5 seconds.
* **Toggling**: The ISR uses the **PINB** hardware toggle trick (`out PINB, reg`) to flip the LED state with a single instruction.
* **The Main Loop**: In this lab, the main loop is simply an infinite `rjmp` to itself, demonstrating that the hardware is now doing the "heavy lifting" for the timing.

---

## Commands

Execute these commands from the project root using the `ninja` build tool.

### 1. Simulation (The Virtual Environment)
* **Start Visualizer**: `ninja -C build 02-timedblink-view`
  * *Opens the graphical LED window and waits for the timer-driven socket connection.*
* **Start MCU**: `ninja -C build 02-timedblink-run`
  * *Observe how the simulator handles interrupts by watching the program counter jump to the vector table.*

### 2. Deployment (The Real World)
* **Flash Hardware**: `ninja -C build 02-timedblink-flash`
  * *Deploys the timer-driven assembly code to your physical Arduino Uno.*
* **Debug Flash**: `ninja -C build 02-timedblink-flash-debug`
  * *Provides a full verbose report of the hardware handshake and memory writing process.*

### 3. Advanced: Extraction & Analysis
* **Recover Firmware**: `ninja -C build flash-recover`
  * *Dumps the chip's current Flash memory to `global_backup.hex`.*
* **Disassemble**: `avr-objdump -m avr5 -D global_backup.hex`
  * *Challenge: Locate the Interrupt Vector Table at the beginning of the disassembly and find the `jmp` instruction pointing to your ISR.*

---

## Troubleshooting

* **LED Blinks too Fast**: Ensure you have correctly set the three prescaler bits (CS12, CS11, CS10) in the `TCCR1B` register for the 1024 divider.
* **Interrupt Never Fires**: Double-check that you have executed the `sei` (Set Global Interrupt) instruction in your setup code. Without this, the CPU will ignore the timer's compare signals.
* **Simulation Mismatch**: If the virtual LED doesn't blink but the real one does, ensure the Unix Socket path in `02-timedblink/meson.build` is unique to this lab.
