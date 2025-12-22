# labs/atmega328p/01-blink/simulator/meson.build

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
