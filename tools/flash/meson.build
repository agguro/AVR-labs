# /tools/flash/meson.build

flash_exe = executable(
  'flash',
  'flash-new.c',
  install: true,
  install_dir: 'bin'
)

flash_command = [flash_exe]

# Global Recovery Command
# This allows students to run 'ninja flash-recover' from anywhere
run_target('flash-recover',
    command: [flash_exe, '-r', 'global_backup.hex', 'uno']
)
