#!/bin/bash
set -e

# ================================================
#   Arduino Sketch → avr-gcc Build System
#   FINAL CLEAN VERSION
#   • full Arduino core + variant build
#   • C / C++ / ASM
#   • C++11 enabled
#   • -save-temps=obj
#   • ALL temp files moved to reversed/
# ================================================

SKETCH="$1"
ACTION1="$2"
ACTION2="$3"

if [[ ! -f "$SKETCH" ]]; then
    echo "Usage: $0 <sketch.ino> [flash] [qemu]"
    exit 1
fi

# ------------------------------------------------
#   SETTINGS
# ------------------------------------------------

MCU="atmega328p"
F_CPU="16000000L"
PORT=${PORT:-/dev/ttyACM0}

CORE="/usr/share/arduino/hardware/arduino/avr/cores/arduino"
VARIANT="/usr/share/arduino/hardware/arduino/avr/variants/standard"

RED="\e[31m"; GREEN="\e[32m"; CYAN="\e[36m"; YELLOW="\e[33m"; END="\e[0m"

echo -e "${CYAN}Using core:    $CORE${END}"
echo -e "${CYAN}Using variant: $VARIANT${END}"

# ------------------------------------------------
#   DIRECTORIES
# ------------------------------------------------

BUILD="build"
REVERSED="reversed"

mkdir -p "$BUILD"
mkdir -p "$REVERSED"

BASE=$(basename "$SKETCH" .ino)
CPP="$BUILD/$BASE.cpp"
ELF="$BUILD/$BASE.elf"
HEX="$BUILD/$BASE.hex"

# ------------------------------------------------
#   MOVE INTERMEDIATE FILES (FINAL CLEAN VERSION)
# ------------------------------------------------

move_intermediates() {
    find "$BUILD" -maxdepth 1 \
        \( -name "*.i" -o -name "*.ii" -o -name "*.s" \
           -o -name "*.mi" -o -name "*.mm" -o -name "*.d" \
           -o -name "*.spec" -o -name "*.o.*" \) \
        -exec mv {} "$REVERSED"/ \;
}

# ------------------------------------------------
#   COMPILATION FUNCTION
# ------------------------------------------------

compile_file() {
    local src="$1"
    local dest="$2"
    local compiler="$3"

    echo -e "${CYAN}$compiler: $src${END}"

    $compiler -v -save-temps=obj \
        -mmcu=$MCU -DF_CPU=$F_CPU -Os -std=gnu++11 \
        -I"$CORE" -I"$VARIANT" -I"$(dirname "$VARIANT")" \
        -c "$src" -o "$dest"

    move_intermediates
}

# ------------------------------------------------
#   STEP 1 — Convert .ino → .cpp
# ------------------------------------------------

echo -e "${GREEN}== Converting .ino → .cpp ==${END}"

{
    echo "#include <Arduino.h>"
    echo "// Auto prototypes"
    grep -E '^[A-Za-z_][A-Za-z0-9_[:space:]]*\(' "$SKETCH" \
        | sed 's/{.*//; s/$/;/' || true
    echo
    echo "// Original source:"
    cat "$SKETCH"
} > "$CPP"

echo "Generated: $CPP"

# ------------------------------------------------
#   STEP 2 — Compile Arduino Core
# ------------------------------------------------

echo -e "${GREEN}== Compiling Arduino Core ==${END}"

CORE_OBJS=""

for f in "$CORE"/*.c; do
    [[ -f "$f" ]] || continue
    OBJ="$BUILD/core_$(basename "$f").o"
    compile_file "$f" "$OBJ" avr-gcc
    CORE_OBJS+=" $OBJ"
done

for f in "$CORE"/*.cpp; do
    [[ -f "$f" ]] || continue
    OBJ="$BUILD/core_$(basename "$f").o"
    compile_file "$f" "$OBJ" avr-g++ 
    CORE_OBJS+=" $OBJ"
done

for f in "$CORE"/*.S "$CORE"/*.s "$CORE"/*.asm; do
    [[ -f "$f" ]] || continue
    OBJ="$BUILD/core_$(basename "$f").o"
    compile_file "$f" "$OBJ" avr-gcc
    CORE_OBJS+=" $OBJ"
done

# ------------------------------------------------
#   STEP 3 — Compile Variant
# ------------------------------------------------

echo -e "${GREEN}== Compiling Variant ==${END}"

for f in "$VARIANT"/*.{c,cpp,S,s,asm}; do
    [[ -f "$f" ]] || continue
    OBJ="$BUILD/variant_$(basename "$f").o"

    case "$f" in
        *.c)  compile_file "$f" "$OBJ" avr-gcc ;;
        *.cpp) compile_file "$f" "$OBJ" avr-g++ ;;
        *.S|*.s|*.asm) compile_file "$f" "$OBJ" avr-gcc ;;
    esac

    CORE_OBJS+=" $OBJ"
done

# ------------------------------------------------
#   STEP 4 — Compile Sketch
# ------------------------------------------------

echo -e "${GREEN}== Compiling Sketch ==${END}"

SKETCH_OBJ="$BUILD/$BASE.o"

avr-g++ -v -save-temps=obj \
    -mmcu=$MCU -DF_CPU=$F_CPU -Os -std=gnu++11 \
    -I"$CORE" -I"$VARIANT" -I"$(dirname "$VARIANT")" \
    -c "$CPP" -o "$SKETCH_OBJ"

move_intermediates

# ------------------------------------------------
#   STEP 5 — Link
# ------------------------------------------------

echo -e "${GREEN}== Linking ==${END}"

avr-g++ -v -mmcu=$MCU $CORE_OBJS "$SKETCH_OBJ" -o "$ELF"

# ------------------------------------------------
#   STEP 6 — HEX + disassembly
# ------------------------------------------------

echo -e "${GREEN}== Creating HEX ==${END}"

avr-objcopy -O ihex -R .eeprom "$ELF" "$HEX"

echo -e "${YELLOW}HEX created: $HEX${END}"

avr-objdump -d "$ELF" > "$BUILD/$BASE.lss"
avr-objdump -S "$ELF" > "$BUILD/$BASE.asm"

# ------------------------------------------------
#   Flash
# ------------------------------------------------

if [[ "$ACTION1" == "flash" || "$ACTION2" == "flash" ]]; then
    avrdude -p $MCU -c arduino -P "$PORT" -b 115200 \
        -D -U flash:w:"$HEX":i
fi

# ------------------------------------------------
#   QEMU
# ------------------------------------------------

if [[ "$ACTION1" == "qemu" || "$ACTION2" == "qemu" ]]; then
    qemu-system-avr -M uno -bios "$HEX" -nographic
fi

echo -e "${GREEN}=== BUILD COMPLETE ===${END}"

