#!/bin/bash
# prune_simavr.sh - Keep only the library files in the simavr submodule

SUBMODULE_DIR="subprojects/simavr"

if [ ! -d "$SUBMODULE_DIR" ]; then
    echo "Error: Submodule directory not found!"
    exit 1
fi

echo "Cleaning up $SUBMODULE_DIR..."

# Move into the submodule
cd "$SUBMODULE_DIR"

# 1. Remove non-essential top-level folders
rm -rf doc
rm -rf examples
rm -rf tests
rm -rf vhci  # Only needed for USB/Linux kernel hacking

# 2. Remove build artifacts and old Makefiles
find . -name "Makefile*" -delete
find . -name "*.pc" -delete
find . -name "*.pdf" -delete

# 3. Remove the standalone 'run_avr' main file
# We don't need this because we are building our own 'bridge'
rm -f simavr/sim/run_avr.c

echo "Pruning complete. Files remaining:"
ls -R simavr/sim | head -n 20
echo "..."
cd ../..
