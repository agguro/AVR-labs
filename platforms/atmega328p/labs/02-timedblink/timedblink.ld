/* timer_blink.ld */
ENTRY(reset)

MEMORY
{
  flash (rx) : ORIGIN = 0x0000, LENGTH = 32K
  ram   (rw) : ORIGIN = 0x0100, LENGTH = 2K
}

SECTIONS
{
  .text :
  {
    KEEP(*(.vectors)) /* Force vectors to stay at the very front */
    *(.text*)         /* Followed by the rest of the code */
  } > flash
}
