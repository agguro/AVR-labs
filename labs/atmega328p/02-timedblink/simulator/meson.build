# labs/atmega328p/02-timedblink/simulator/meson.build

# Define the unique socket path for this lab
socket_path = '/tmp/' + project_lab_name + '.sock'

simulate = executable(
  'simulate',
  'simulate.c',
  dependencies: [ threads_dep ],
  install: true,
  install_dir: lab_bin_dir
)
