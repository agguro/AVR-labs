# AVR Reverse Engineering & Simulation Lab

An environment for reversing, analyzing, and reimplementing ATmega328P firmware. [cite_start]This project bridges the gap between high-level Arduino sketches and low-level assembly optimization. [cite: 8, 15]

## Project Pillars
* [cite_start]**Hosts**: Real-time synchronized simulator engines using `simavr`. 
* [cite_start]**Tools**: Custom hardware utilities like the automated smart-flashing tool. 
* [cite_start]**Labs**: Modular exercises focusing on specific MCU features and reverse engineering workflows.

## Quick Start
1. **Configure**: Run `./configure.sh` to initialize the build system.
2. **Build All**: `meson compile -C build`
3. **Simulate**: `meson compile -C build sim`
4. **Visualize**: `meson compile -C build view`
