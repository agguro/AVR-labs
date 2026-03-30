# AVR Assembly Labs

The labs are guided exercises designed to help you learn how microcontrollers work from the ground up. The focus is on understanding and insight, not on speed or complexity.

## Microcontrollers

The labs are organized per microcontroller (MCU). Each microcontroller has its own architecture, pin layout, and instruction set.

### ATmega328P
📍 `labs/atmega328p/`

This is the recommended microcontroller for all students. It is the heart of the **Arduino Uno** and is world-renowned for its educational value.

**Recommended for:**
- Beginners and students new to low-level programming.
- Understanding the relationship between software and physical pins.
- Learning the fundamentals of Interrupts, Timers, and Serial communication.

### Other Microcontrollers
📍 `labs/<other-mcu>/`

Additional architectures may be present for comparison. These are intended for advanced exploration and are **not recommended as a first choice**.

## Where should I start?

If you are new or unsure where to begin:

➡️ **Start here:** `labs/atmega328p/01-blink/`

This first lab demonstrates how software controls physical hardware. **Note:** No physical hardware is required to begin; you can complete the labs entirely in the simulator.

---

## Technical Stack

We use a modern, industry-standard toolchain to manage the complexity of Assembly development:

* **Assembler**: `avr-as` (GNU Toolchain) for translating code to machine instructions.
* **Build System**: `Meson` & `Ninja` for automated, lightning-fast compilation.
* **Simulation**: `simavr` for cycle-accurate CPU emulation.
* **Deployment**: A custom `flash` utility wrapping `avrdude` for direct hardware interaction.

---

## Getting Started

Follow these steps to set up your environment:

1.  **Configure the Project**:
    ```bash
    ./configure.sh
    ```
    *This checks for dependencies and prepares the build directory.*

2.  **Build the Project**:
    ```bash
    meson compile -C build
    ```
    *This compiles the simulators, tools, and assembly labs.*

3.  **Install the Project (Optional)**:
    ```bash
    meson install -C build
    ```
    *Default install directory is `dist/`. You can change this during configuration using `./configure.sh --prefix /your/path`.*

---

## Integrated Workflow

Each lab supports a "Three-Pillar" workflow:

1.  **SIMULATE**: Run the code on a virtual MCU connected to a virtual LED/Hardware view via Unix Sockets.
2.  **REVERSE**: Use `avr-objdump` to deconstruct binaries and understand the machine code.
3.  **FLASH**: Deploy the same assembly code to a physical Arduino Uno with a single command.

For detailed instructions on running, viewing, and flashing, see the **README.md** inside each specific lab folder.
