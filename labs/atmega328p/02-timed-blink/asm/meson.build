# labs/atmega328p/01-blink/asm/meson.build

# Stage 1: Assemble the reversed source into an object file
timed-blink_obj = custom_target(
    'timed-blink-o',
    input: 'timed-blink.s',
    output: 'timed-blink.o',
    command: [ avr_as, '-mmcu=' + mcu, '-o', '@OUTPUT@', '@INPUT@' ],
    install: false
)

# Stage 2: Link
blink_elf = custom_target(
    'timed-blink-elf',
    input: [ timed-blink_obj, 'timed-blink.ld' ],
    output: 'timed-blink.elf',
    command: [ avr_ld, '-T', '@INPUT1@', '-o', '@OUTPUT@', '@INPUT0@' ],
    install: true,
    install_dir: lab_bin_dir  # <--- Use the variable
)

# Stage 3: Extract HEX
blink_hex = custom_target(
    'timed-blink-hex',
    input: timed-blink_elf,
    output: 'timed-blink.hex',
    command: [ avr_objcopy, '-O', 'ihex', '@INPUT@', '@OUTPUT@' ],
    build_by_default: true,
    install: true,
    install_dir: lab_bin_dir
)

