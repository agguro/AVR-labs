CC = gcc
AVRCC = avr-gcc
OBJCOPY = avr-objcopy

MCU = atmega328p
F_CPU = 16000000UL

FW_SRC = firmware.c
FW_ELF = firmware.elf
FW_HEX = firmware.hex

SIM_SRC = simavr_led_bridge.c
SIM_BIN = bridge  # Naam korter gemaakt voor gemak

# Gebruik pkg-config voor simavr, maar voeg expliciet pthread toe
CFLAGS = -Wall -Wextra -O2 $(shell pkg-config --cflags simavr 2>/dev/null || echo "-I/usr/local/include")
LDFLAGS = $(shell pkg-config --libs simavr 2>/dev/null || echo "-L/usr/local/lib -lsimavr -lelf") -lm -lpthread

.PHONY: all clean

all: $(FW_ELF) $(FW_HEX) $(SIM_BIN)

# Firmware compile
$(FW_ELF): $(FW_SRC)
	$(AVRCC) -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -o $(FW_ELF) $(FW_SRC)

$(FW_HEX): $(FW_ELF)
	$(OBJCOPY) -O ihex $(FW_ELF) $(FW_HEX)

# Simulator bridge compile
$(SIM_BIN): $(SIM_SRC)
	$(CC) $(SIM_SRC) -o $(SIM_BIN) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(FW_ELF) $(FW_HEX) $(SIM_BIN)
