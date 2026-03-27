# labs/atmega328p/02-timedblink/asm/meson.build

# Stage 1: Assemble the reversed source into an object file
timedblink_obj = custom_target(
    'timedblink-o',
    input: 'timedblink.s',
    output: 'timedblink.o',
    command: [ avr_as, '-mmcu='+mcu , '-o', '@OUTPUT@', '@INPUT@' ],
    install: false
)

# Stage 2: Link
timedblink_elf = custom_target(
    'timedblink-elf',
    input: [ timedblink_obj, 'timedblink.ld' ],
    output: 'timedblink.elf',
    command: [ avr_ld, '-m'+emulation,'-T', '@INPUT1@', '-o', '@OUTPUT@', '@INPUT0@' ],
    install: true,
    install_dir: lab_bin_dir  # <--- Use the variable
)

# Stage 3: Extract HEX
timedblink_hex = custom_target(
    'timedblink_hex',
    input: timedblink_elf,
    output: 'timedblink.hex',
    command: [ avr_objcopy, '-O', 'ihex', '@INPUT@', '@OUTPUT@' ],
    build_by_default: true,
    install: true,
    install_dir: lab_bin_dir
)

