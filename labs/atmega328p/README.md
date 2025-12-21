# Lab 01: Blink (The Reverse Engineering Cycle)

[cite_start]This lab demonstrates the complete workflow of deconstructing an Arduino Blink sketch and recreating it in cycle-accurate Assembly. [cite: 8, 15]

## Workflow
1. [cite_start]**Reversing**: Automated extraction of assembly from C++ code. [cite: 20]
2. **Implementation**: Manual, optimized assembly programming with stack control.
3. [cite_start]**Simulation**: Real-time verification via Unix Domain Sockets. [cite: 1]
4. [cite_start]**Flashing**: Direct hardware deployment via the custom flash tool. [cite: 6]

## Commands
* **Extract Assembly**: `meson compile -C build reversing`
* **Upload to Hardware**: `meson compile -C build flash`
