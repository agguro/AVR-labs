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
