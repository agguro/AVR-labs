# /meson.build

project('avr-labs', 'c', 'cpp', version: '0.1')

# 1. Load your fork as a subproject (The "Internal" Dependency)
# This replaces the system-wide 'simavr' dependency
sim_proj = subproject('simavr')
sim_dep = sim_proj.get_variable('simavr_dep')

# 2. Native Dependencies
threads_dep = dependency('threads')

# 3. AVR Tool Discovery (For your .s and .c firmware)
avr_gcc     = find_program('avr-gcc', required: true)
avr_gpp     = find_program('avr-g++', required: true)
avr_size    = find_program('avr-size', required: true)
avr_as      = find_program('avr-as', required: true)
avr_ld      = find_program('avr-ld', required: true)
avr_objcopy = find_program('avr-objcopy', required: true)

# 5. Subsystems
# Now that 'sim_dep' and 'bridge' are defined, we can run the labs
subdir('labs')
