# Smart Flash Tool

[cite_start]A robust C-based replacement for complex `avrdude` commands. [cite: 24]

## Features
* **Auto-Detection**: Automatically finds serial ports at `/dev/ttyACM*` or `/dev/ttyUSB*`.
* **Baud Probing**: Iterates through 115200, 57600, and 19200 baud to find the correct bootloader speed.
* **Safety**: Performs a "dry run" probe before attempting a destructive flash write.

## CLI Usage
`./flash <firmware.hex> [mcu_type]`
