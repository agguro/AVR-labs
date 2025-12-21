# labs/atmega328p/meson.build

# ATmega family
mcu = 'atmega328p'
f_cpu = '16000000L'

# --- Arduino Environment Paths ---
# We define these here so every sub-lab can find the Arduino headers
arduino_base_path = '/usr/share/arduino/hardware/arduino/avr'
core_src_path     = arduino_base_path / 'cores/arduino'
variant_src_path  = arduino_base_path / 'variants/standard'

# --- Global Arduino Compiler Flags ---
# Used for reversing and analysis targets
arduino_compile_args = [
    '-mmcu=' + mcu,
    '-DF_CPU=' + f_cpu,
    '-Os',
    '-std=gnu++11',
    '-save-temps=obj',
    '-fno-exceptions',
    '-ffunction-sections',
    '-fdata-sections'
]

arduino_inc = include_directories(
    core_src_path,
    variant_src_path
)

# --- Labs ---
subdir('01-blink')
