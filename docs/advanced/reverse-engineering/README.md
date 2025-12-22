[Home](../../../README.md)  -  [Docs index](../../index/README.md)
[🇬🇧](README.md)  -  [🇳🇱](README.nl.md)  -  [🇨🇴](README.es-co.md)  -  [🇵🇹](README.pt.md)

# Studying compiled firmware (advanced)

This document introduces the study of compiled firmware for educational purposes.  
It is intended for advanced learners who want to understand what remains of a program once source code is no longer available.

This topic is optional and not required to complete the main learning paths.

---

## What is meant by “reverse engineering” here

In this context, reverse engineering means analysing compiled firmware to understand its structure, behaviour, and limitations.  
The goal is **not** to reconstruct source code or bypass protections.

The focus is on learning how microcontrollers execute machine-level instructions.

---

## What can be analysed

Learners may study:

- `.elf` files, with or without debug symbols  
- `.hex` files representing raw firmware images  

These files can originate from:
- firmware built within this repository  
- openly available examples  
- the learner’s own projects  

---

## Educational goals

By analysing compiled firmware, learners can:

- observe how high-level code is translated into instructions  
- understand memory layout and execution flow  
- recognise the impact of compiler optimisations  
- appreciate the role of symbols and debug information  

---

## Questions to explore

Examples of questions suitable for this topic include:

- Can you identify loops or delays in the compiled code?  
- Can you recognise input/output operations?  
- What information is lost when debug symbols are removed?  
- Why is it difficult to reconstruct source code from firmware?  

---

## Tools and approach

Various tools can assist in this exploration, such as:

- disassemblers  
- symbol inspection tools  
- simulators  
- custom analysis scripts  

The emphasis is on **observation and interpretation**, not automation.

---

## Scope and limitations

This activity focuses on understanding, not reconstruction.  
Recovering original source code from firmware is generally not possible.

Any conclusions drawn should be treated as informed interpretations.

---

## Ethical and legal note

This topic is intended for educational use only.  
Learners should work with their own firmware or with openly available examples, and must respect software licenses.

---

## When to explore this topic

This topic is best approached:

- after completing the core learning paths  
- with prior knowledge of assembly and microcontroller architecture  
- under guidance when used in an educational setting  

This section exists to deepen understanding and satisfy curiosity.

