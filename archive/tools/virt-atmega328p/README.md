# ATmega328P Simulator Host

[cite_start]The core simulation engine that runs the MCU firmware with high precision. [cite: 21]

## Technical Features
* **Lockdown Sync**: Synchronizes simulation cycles with the system clock for 1:1 real-time performance (16MHz).
* **GPIO Streaming**: Broadcasts state changes for PORTB Pin 5 to a Unix Domain Socket at `/tmp/simavr_gpio.sock`.
* **Runtime Tuning**: 
    * Press `+` to double simulation frequency.
    * Press `-` to halve simulation frequency.
    * Press `q` to quit the simulator.
