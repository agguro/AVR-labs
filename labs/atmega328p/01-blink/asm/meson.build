# labs/atmega328p/01-blink/asm/meson.build

# Stage 1: Assemble the reversed source into an object file
blink_obj = custom_target(
    'blink-o',
    input: 'blink.s',
    output: 'blink.o',
    command: [ avr_as, '-mmcu=' + mcu, '-o', '@OUTPUT@', '@INPUT@' ],
    install: false
)

# Stage 2: Link
blink_elf = custom_target(
    'blink-elf',
    input: [ blink_obj, 'blink.ld' ],
    output: 'blink.elf',
    command: [ avr_ld, '-T', '@INPUT1@', '-o', '@OUTPUT@', '@INPUT0@' ],
    install: true,
    install_dir: lab_bin_dir  # <--- Use the variable
)

# Stage 3: Extract HEX
blink_hex = custom_target(
    'blink-hex',
    input: blink_elf,
    output: 'blink.hex',
    command: [ avr_objcopy, '-O', 'ihex', '@INPUT@', '@OUTPUT@' ],
    build_by_default: true,
    install: true,
    install_dir: lab_bin_dir  # <--- Use the variable
)

# Stage 4: Flash target to upload the HEX file to the physical hardware
# Usage: meson compile -C build flash
run_target('flash',
    command: [
        'avrdude',
        '-p', mcu,
        '-c', 'arduino',      # Programmer type for Uno
        '-P', '/dev/ttyACM0', # Default port, you can make this a variable
        '-b', '115200',       # Baud rate for Uno
        '-U', 'flash:w:@0@:i'.format(blink_hex.full_path())
    ],
    depends: blink_hex        # Ensure the HEX is built before flashing
)
