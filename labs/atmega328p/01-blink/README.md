# Lab 01: Blink (The Reverse Engineering Cycle)

This lab demonstrates the complete workflow of deconstructing an Arduino Blink sketch and recreating it in cycle-accurate Assembly.

## Workflow
1. **Reversing**: Automated extraction of assembly from C++ code.
2. **Implementation**: Manual, optimized assembly programming with stack control.
3. **Simulation**: Real-time verification via Unix Domain Sockets.
4. **Flashing**: Direct hardware deployment via the custom flash tool.

## Commands
* **Extract Assembly**: `meson compile -C build reversing`
* **Upload to Hardware**: `meson compile -C build flash`
