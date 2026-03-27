# labs/atmega328p/02-timedblink/meson.build

project_lab_name = '02-timedblink'
lab_socket_path  = '/tmp/' + project_lab_name + '.sock'

# 1. Build the specific parts for this lab
# Note: subdir('asm') will define 'timedblink_elf'
subdir('asm')        
subdir('simulator')  

# 2. Create the unique Ninja commands for this specific lab
run_target(project_lab_name + '-run',
    command: [virt_mcu_bin, timedblink_elf, lab_socket_path]
)

run_target(project_lab_name + '-view',
    command: [simulate, lab_socket_path]
)

run_target(project_lab_name + '-flash',
    command: [flash_exe,'-v', timedblink_hex]
)

