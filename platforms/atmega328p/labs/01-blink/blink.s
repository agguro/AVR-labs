; labs/atmega328p/01-blink/asm/blink.s

; ============================================================
; Project: 01-Blink (Reverse Engineered)
; Target:  ATmega328P
; Description: Toggles PB5 (Built-in LED) with stack setup
; ============================================================

    .section .text
    .global reset

    .org 0x0000
reset:
    rjmp start

start:
    ; Initialize Stack Pointer (RAMEND = 0x08FF)
    ; Required for rcall/ret functionality
    ldi r16, 0x08
    out 0x3e, r16    ; SPH (Stack Pointer High)
    ldi r16, 0xff
    out 0x3d, r16    ; SPL (Stack Pointer Low)

    ; Set PB5 as Output (DDRB bit 5 = 1)
    ; DDRB is at I/O address 0x04
    sbi 0x04, 5

loop:
    sbi 0x05, 5      ; LED ON (PORTB 5 = 1)
    rcall delay
    cbi 0x05, 5      ; LED OFF (PORTB 5 = 0)
    rcall delay
    rjmp loop

; --- Delay Subroutine (~0.5s at 16MHz) ---
delay:
    ldi r18, 8       ; Outer loop
d3:
    ldi r19, 255     ; Middle loop
d2:
    ldi r20, 255     ; Inner loop
d1:
    dec r20          ; 1 cycle
    brne d1          ; 2 cycles (taken)
    dec r19
    brne d2
    dec r18
    brne d3
    ret              ; Pop return address from stack and jump
