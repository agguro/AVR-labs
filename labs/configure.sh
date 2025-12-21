#!/bin/sh
# ================================================================= #
# AVR Labs Project Configuration Script                             #
# ================================================================= #
set -e

# ANSI Color Codes for professional terminal output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "${BLUE}====================================================${NC}"
echo "${BLUE}          AVR Labs Project Configuration            ${NC}"
echo "${BLUE}====================================================${NC}"

# ------------------------------------------------------------
# Helper Functions
# ------------------------------------------------------------
check_cmd() {
    printf "Checking for %-15s ... " "$1"
    if command -v "$1" >/dev/null 2>&1; then
        echo "${GREEN}[YES]${NC}"
    else
        echo "${RED}[NO]${NC}"
        EXIT_STATUS=1
    fi
}

check_pkg() {
    printf "Checking for lib %-11s ... " "$1"
    if pkg-config --exists "$1"; then
        RAW_VERSION=$(pkg-config --modversion "$1")
        VERSION=$(echo "$RAW_VERSION" | sed 's/[^0-9.]//g')
        PC_PATH=$(pkg-config --variable=pcfiledir "$1")
        
        # Check if it's a custom build (in /usr/local)
        if echo "$PC_PATH" | grep -q "/usr/local"; then
            LOCATION_LABEL="${GREEN}[CUSTOM]${NC}"
        else
            LOCATION_LABEL="${YELLOW}[SYSTEM]${NC}"
        fi

        echo "${GREEN}[YES]${NC} (v$VERSION) $LOCATION_LABEL"
        
        if [ "$1" = "simavr" ] && [ "$LOCATION_LABEL" = "${YELLOW}[SYSTEM]${NC}" ]; then
             echo "${YELLOW}  --> Note: You are using the system simavr. GitHub version is recommended.${NC}"
        fi
    else
        echo "${RED}[NO]${NC}"
        EXIT_STATUS=1
    fi
}

# Initial status
EXIT_STATUS=0

# ------------------------------------------------------------
# System Environment Check
# ------------------------------------------------------------
echo "System Info: $(uname -s) $(uname -r) ($(uname -m))"
echo "----------------------------------------------------"

# Basic Build Tools
check_cmd meson
check_cmd ninja
check_cmd cc
check_cmd pkg-config

# AVR Toolchain
check_cmd avr-as
check_cmd avr-ld
check_cmd avr-objcopy
check_cmd avrdude

# Libraries
check_pkg simavr

echo "----------------------------------------------------"

# Handle missing dependencies
if [ $EXIT_STATUS -ne 0 ]; then
    echo "${RED}Error: Configuration failed due to missing dependencies.${NC}"
    echo "Please install the required tools and run this script again."
    exit 1
fi

# ------------------------------------------------------------
# Meson Build Configuration
# ------------------------------------------------------------
# Set default installation prefix to 'dist' folder in current directory
PREFIX="${PREFIX:-$PWD/dist}"
BUILD_DIR="build"

echo "Configuration settings:"
echo " - Installation Prefix: $PREFIX"
echo " - Build Directory:    $BUILD_DIR"
echo

# If build directory exists, reconfigure; otherwise, setup new
if [ -d "$BUILD_DIR" ]; then
    echo "${YELLOW}Existing build directory found. Reconfiguring...${NC}"
    meson setup "$BUILD_DIR" --reconfigure --prefix="$PREFIX" "$@"
else
    echo "${BLUE}Creating new build directory...${NC}"
    meson setup "$BUILD_DIR" --prefix="$PREFIX" "$@"
fi

echo
echo "${GREEN}Configuration successful!${NC}"
echo "----------------------------------------------------"
echo "Next steps:"
echo "  1. Compile the project:   ${BLUE}meson compile -C $BUILD_DIR${NC}"
echo "  2. Run the simulator:     ${BLUE}./$BUILD_DIR/hosts/atmega328p/virt-atmega328p${NC}"
echo "  3. Flash to Arduino:      ${BLUE}meson compile -C $BUILD_DIR flash${NC}"
echo "----------------------------------------------------"
