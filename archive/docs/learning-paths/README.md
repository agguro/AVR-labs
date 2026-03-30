[Home](../../README.md)  -  [Docs index](../index/README.md) <br>
[🇬🇧](README.md)  -  [🇳🇱](README.nl.md)  -  [🇨🇴](README.es-co.md)  -  [🇵🇹](README.pt.md)

# Learning Paths

This repository supports multiple learning paths, depending on prior knowledge, available tools, and learning goals.  
All paths ultimately lead to the same objective: understanding how microcontrollers really work.

Not everyone starts from the same place, and this is a deliberate design choice.

---

## 🟢 Path 1 — Guided Entry (Arduino Bridge)

**For:**  
- beginners  
- younger learners  
- students without a full toolchain  
- a first encounter with microcontrollers  

**Tools:**  
- Arduino IDE  
- Arduino sketches (in the `arduino/` directory)  

**Focus:**  
- basic input and output  
- observing behaviour  
- simple experiments  

**What you do in this path:**  
- open a provided sketch  
- upload it to an Arduino board  
- observe LEDs, buttons, and timing  

**What you learn:**  
- that code controls hardware  
- that pins have meaning  
- that timing matters  

**Important note:**  
This path is an entry point, not the final destination.  
Learners are encouraged to progress to Path 2 once they feel comfortable.

---

## 🟡 Path 2 — Simulation First (Core Path)

**For:**  
- learners who want to understand what is really happening  
- environments without physical hardware  
- classrooms with limited resources  

**Tools:**  
- `virt-atmega328p`  
- a `simulate` program per lab  
- Meson build system  

**Focus:**  
- internal microcontroller behaviour  
- registers and ports  
- timing and execution  

**What you do in this path:**  
- build firmware as `.elf` files  
- run firmware in simulation  
- interact with virtual components  

**What you learn:**  
- how firmware is executed  
- how ports actually work  
- the difference between simulation and real hardware  

👉 **This is the recommended learning path.**

---

## 🔵 Path 3 — Firmware and Flashing (Hardware-Aware)

**For:**  
- learners ready to work with real hardware  
- anyone curious about what “uploading” really means  

**Tools:**  
- `.hex` firmware files  
- the `flash` tool  
- ATmega328P hardware (with or without an Arduino board)  

**Focus:**  
- flashing versus uploading  
- memory layout  
- serial communication  

**What you do in this path:**  
- flash firmware directly to the microcontroller  
- configure baud rate and ports  
- observe behaviour on real hardware  

**What you learn:**  
- how code reaches the microcontroller  
- what a bootloader does  
- how software tools communicate with hardware  

---

## 🔴 Path 4 — Advanced Exploration (Beyond Arduino)

**For:**  
- advanced learners  
- self-directed students  
- those interested in embedded system design  

**Tools:**  
- extensions to `virt-atmega328p`  
- virtual components  
- low-level debugging  

**Focus:**  
- system design  
- peripherals  
- architecture  

**What you do in this path:**  
- extend the virtual microcontroller  
- design custom virtual hardware  
- explore timing, interrupts, and memory  

**What you learn:**  
- how embedded systems are structured  
- how hardware and software interact  
- how abstractions are created  

---

## 🔁 Paths are not strictly separated

Learners are free to move between paths.  
Someone may start with Arduino, switch to simulation, and later return to hardware with deeper understanding.

The goal is progression, not restriction.

---

## 🎯 Shared goal

Not just to make something work,  
but to understand **why** it works.

---

## Note for educators

These learning paths are intentionally designed to work without mandatory physical hardware.  
They enable equal learning opportunities in environments where resources are limited, without sacrificing technical depth.

