# tools/virt-atmega328p/meson.build

virt_atmega328p = executable(
  'virt-atmega328p',
  'virt-atmega328p.c',
  dependencies: [simavr_dep, threads_dep],
  install: true
)

# This line is the secret sauce: 
# It tells the Labs to use the 'executable' object we just made
virt_mcu_bin = virt_atmega328p
