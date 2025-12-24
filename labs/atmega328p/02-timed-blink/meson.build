# labs/atmega328p/02-timed-blink/meson.build

# Project-level definition for this lab
project_lab_name = '02-timed-blink'

# Ensure 'mcu' is defined (usually passed from the parent directory)
# We use join_paths or the / operator, but ensure both are strings
lab_bin_dir = mcu / project_lab_name / 'bin'

# Now call the sub-components
subdir('asm')
subdir('simulator')

