# labs/atmega328p/meson.build

# Shared Hardware Specs
mcu       = 'atmega328p'
emulation = 'avr5'
f_cpu     = '16000000L'

# Global lab binary directory (if you want all bins in one place)
lab_bin_dir = meson.current_build_dir() / 'bin'

# List the labs to be processed
subdir('01-blink')
subdir('02-timedblink')

