# labs/atmega328p/01-blink/simulator/meson.build

# Simulation Host
virt_atmega328p = executable(
  'virt-atmega328p',
  '../../../hosts/atmega328p/virt-atmega328p.c',
  dependencies: [ simavr_dep, threads_dep ],
  install: false
)

# Visualization Dashboard
simulate = executable(
  'simulate',
  'simulate.c',
  dependencies: [ threads_dep ],
  install: true,
  install_dir: lab_bin_dir
)

# Convenience target to launch the visualizer
run_target('view',
  command: [simulate]
)
