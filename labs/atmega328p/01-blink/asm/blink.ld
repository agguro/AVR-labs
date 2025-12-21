/* labs/atmega328p/01-blink/asm/blink.ld */

/* Linker script for ATmega328P 
 * Defines memory layout and section placement
 */

ENTRY(reset) /* Define the entry point of the program */

MEMORY
{
  /* 32KB of internal Flash memory for code */
  flash (rx) : ORIGIN = 0x0000, LENGTH = 32K
  
  /* 2KB of internal SRAM for data (starts after registers/IO) */
  ram   (rw) : ORIGIN = 0x0100, LENGTH = 2K
}

SECTIONS
{
  /* Place all code and constants into Flash */
  .text :
  {
    *(.text*)
  } > flash
}
