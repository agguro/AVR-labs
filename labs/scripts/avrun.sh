#!/bin/bash
# Usage: ./avrun.sh [lab_name] [action: sim|flash]
LAB=$1
ACTION=$2
PREFIX="/home/agguro/my_avr_tools/atmega328p"

if [ "$ACTION" == "sim" ]; then
    # Launch simulator host with the lab's elf
    $PREFIX/$LAB/bin/virt-atmega328p $PREFIX/$LAB/bin/blink.elf &
    # Launch the dashboard
    sleep 1
    $PREFIX/$LAB/bin/simulate
elif [ "$ACTION" == "flash" ]; then
    avrdude -p atmega328p -c arduino -P /dev/ttyACM0 -b 115200 -U flash:w:$PREFIX/$LAB/bin/blink.hex:i
fi
