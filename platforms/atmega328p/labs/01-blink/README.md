# Lab 01: Blink (The Reverse Engineering Cycle)

This lab demonstrates the complete workflow of deconstructing an AVR binary and recreating it in pure, cycle-accurate Assembly. Students will move from high-level C++ abstraction down to direct register manipulation.

## Hardware Setup

While the Arduino has a built-in LED on Pin 13, you can connect an external LED for better visibility:

1. **LED Anode (Long Leg)**: Connect to **Digital Pin 13**.
2. **Resistor (220Ω)**: Connect one end to the **LED Cathode (Short Leg)** and the other to **GND**.
3. **Resistor Color Code**: Red-Red-Brown (indicates 220 ohms).

*Note: The ATmega328P bit for this pin is **PB5** (Bit 5 of Port B).*

## Workflow

1. **Reversing**: Extracting logic from an existing binary to understand hardware initialization.
2. **Implementation**: Writing manual, optimized Assembly code with full control over the stack and I/O registers.
3. **Simulation**: Real-time verification using **simavr** and a custom LED visualizer connected via Unix Domain Sockets.
4. **Flashing**: Direct hardware deployment to the ATmega328P using the project's custom `flash` utility.

---

## How the Program Works

The Assembly code in this lab performs three critical hardware tasks:
* **Stack Initialization**: Manually setting the Stack Pointer (`SPH` and `SPL`) to the top of internal SRAM to allow for subroutines and interrupts.
* **Data Direction**: Configuring the `DDRB` register to set Pin 5 (the Arduino built-in LED) as a digital output.
* **Logic Loop**: Toggling the LED state and executing a nested delay loop to match human visual persistence.

---

## Commands

Execute these commands from the project root using the `ninja` build tool.

### 1. Simulation (The Virtual Environment)
Always verify your logic in the simulator before touching the hardware.
* **Start Visualizer**: `ninja -C build 01-blink-view`
  * *Opens the graphical LED window and waits for a socket connection.*
* **Start MCU**: `ninja -C build 01-blink-run`
  * *Launches the virtual ATmega328P and connects to the visualizer.*

### 2. Deployment (The Real World)
Once simulation is successful, push the code to your physical Arduino Uno.
* **Flash Hardware**: `ninja -C build 01-blink-flash`
  * *Automatically detects the serial port and uploads via avrdude.*
* **Debug Flash**: `ninja -C build 01-blink-flash-debug`
  * *Provides a full verbose report, including device signature and fuse settings.*

### 3. Advanced: Recovery & Decompilation
For practicing reverse engineering on existing hardware:
* **Recover Firmware**: `ninja -C build flash-recover`
  * *Dumps the chip's current Flash memory to `global_backup.hex`.*
* **Disassemble**: `avr-objdump -m avr5 -D global_backup.hex`
  * *Translates the recovered machine code back into human-readable Assembly instructions.*

---

## Troubleshooting

* **Connection Refused**: Ensure you start the `view` command before the `run` command. The visualizer acts as the socket server.
* **Permission Denied**: If you cannot access the USB port during flashing, add your user to the dialout group:
  `sudo usermod -a -G dialout $USER` (requires logout/login).
* **LED Constantly On**: Your delay loop may be too fast. At 16MHz, a 16-bit register overflows in milliseconds; use nested loops for a visible 1Hz blink.
