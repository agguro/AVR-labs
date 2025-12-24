# meson.build

project('avr-labs', 'c', 'cpp', version: '0.1')

# 1. Native Dependencies (for Linux tools)
simavr_dep  = dependency('simavr', required: true)
threads_dep = dependency('threads')

# 2. AVR Tool Discovery (Manual)
avr_gcc     = find_program('avr-gcc', required: true)
avr_gpp     = find_program('avr-g++', required: true)
avr_size    = find_program('avr-size', required: true)
avr_as      = find_program('avr-as', required: true)
avr_ld      = find_program('avr-ld', required: true)
avr_objcopy = find_program('avr-objcopy', required: true)

# Your custom host simulator (the one we just adjusted)
virt_mcu_bin = []

# 3. Subsystems
subdir('tools')			# first build tools
subdir('labs')

