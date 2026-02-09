# RISC-V RV32IM Virtual Machine

COSC 530 – Computer Architecture  
Author: Jarrod Romero

---

## Overview

This project implements a **virtual machine (VM)** that emulates the **RISC-V RV32IM instruction set architecture**.  
The VM models the core components of a simple computer, including memory, registers, and control state, and is being developed incrementally as part of a multi-stage course project.

This repository currently contains the implementation for **Part I: Machine Setup**.

---

## Implemented Features (Part I)

### ✔ Machine Architecture
- RV32IM (32-bit RISC-V with integer and multiplication/division extensions)
- 32 general-purpose registers (`x0`–`x31`)
- Program Counter (`PC`)
- Stack Pointer initialized according to RISC-V ABI
- Byte-addressable main memory

### ✔ Memory
- 1 MiB (2²⁰ bytes) of RAM
- Memory is intentionally left uninitialized
- Memory addresses map directly to byte indices

### ✔ Registers
- 32 × 32-bit integer registers
- `x0` is hard-wired to zero (reads return 0, writes are ignored)
- Register access via a clean read/write API

### ✔ Program Counter
- Separate from the register file
- Initialized to 0 (to be updated during ELF loading in Part II)

### ✔ Stack Pointer
- Register `x2` initialized to the top of memory
- Stack grows downward, following RISC-V conventions

### ✔ Sign Extension Utility
- Generic sign-extension helper function
- Works for immediates of varying bit widths
- Implemented **without loops or conditionals**, as required

### ✔ Boot Banner & Debug Output
- Optional ASCII boot banner
- Fake boot delay for visual clarity
- Colorized debug output using ANSI escape codes
- No impact on VM functionality

---

## Project Structure
```bash
riscv_vm/
├── include/
│ ├── memory.hpp
│ ├── registers.hpp
│ ├── machine.hpp
│ └── utils.hpp
│
├── src/
│ ├── memory.cpp
│ ├── registers.cpp
│ ├── machine.cpp
│ └── main.cpp
│
├── Makefile
└── README.md



---

## Building the Project

### Requirements
- C++17-compatible compiler (`g++`)
- Linux / WSL / MSCS VM environment
- Make

### Build Instructions

```bash
make clean
make
./riscv_vm

### Example Out

Booting RISC-V VM...

██████╗ ██╗███████╗ ██████╗              ██╗   ██╗
██╔══██╗██║██╔════╝██╔════╝              ██║   ██║
██████╔╝██║███████╗██║         █████╗    ██║   ██║
██╔══██╗██║╚════██║██║         ╚════╝    ╚██╗ ██╔╝
██║  ██║██║███████║╚██████╗               ╚████╔╝
╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝                ╚═══╝

RISC-V Machine initialized
Memory Size : 1048576 bytes (1 MiB)
Stack Ptr   : 0x100000
PC          : 0
