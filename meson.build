# labs/meson.build

project('avr-labs', 'c', 'cpp', version: '0.1')

# 1. Native Dependencies (for Linux tools)
simavr_dep  = dependency('simavr', required: true)
threads_dep = dependency('threads')

# 2. AVR Tool Discovery (Manual)
avr_gcc     = find_program('avr-gcc')
avr_gpp     = find_program('avr-g++')
avr_objcopy = find_program('avr-objcopy')
avr_size    = find_program('avr-size')
avr_as      = find_program('avr-as', required: true)
avr_ld      = find_program('avr-ld', required: true)
avr_objcopy = find_program('avr-objcopy', required: true)

# 3. Common AVR Variables
mcu   = 'atmega328p'
f_cpu = '16000000L'

# 4. Subsystems
subdir('hosts')         # Compiled with host GCC
subdir('tools')         # Compiled with host GCC
subdir('atmega328p')    # Uses Custom Targets to call avr-gcc
