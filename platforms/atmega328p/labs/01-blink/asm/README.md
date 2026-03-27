# Optimized Assembly

Contains the hand-written, cycle-accurate implementation of the blink logic.

## Technical Details
* **Stack Setup**: Explicit initialization of the Stack Pointer High (SPH) and Low (SPL) bytes.
* **Vector Table**: Proper placement of the reset vector at address `0x0000`.
* **Timing Loops**: Triple-nested delay loops optimized for 16MHz operation without using hardware timers.
