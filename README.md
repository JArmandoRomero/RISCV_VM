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

## Part II: ELF Loader

### Objective
Implement an ELF loader for a **32-bit, little-endian RISC-V** emulator.  
The loader validates an ELF executable, loads its segments into memory, and sets the program counter to the entry point.

---

### Target Constraints
- Architecture: RISC-V  
- Bit Width: 32-bit  
- Endianness: Little-endian  
- File Type: Executable ELF only  
- ELF Header Size: 52 bytes  

---

### ELF Header (EH)
The ELF header is located at the start of the file and is used to verify compatibility and locate the program header table.

#### Required Validation Checks
- `e_ident` must equal `\x7fELF`
- `e_type` must be `2` (executable)
- `e_machine` must be `243` (RISC-V)
- `e_bitsize` must be `1` (32-bit)

#### Key Header Fields
- `e_entry` – Program entry point  
- `e_phoff` – Program header table offset  
- `e_phnum` – Number of program headers  
- `e_phentsize` – Size of each program header  

---

### Program Header Table (PH)
- Located at `e_phoff`
- Contains `e_phnum` entries
- Each program header is 32 bytes

---

### Program Header Fields
- `p_type` – Segment type (`PT_LOAD = 1`)
- `p_offset` – File offset of segment data
- `p_vaddr` – Virtual memory load address
- `p_filesz` – Number of bytes to copy from file
- `p_memsz` – Number of bytes allocated in memory

---

### Loading Rules
- Only segments with `p_type == PT_LOAD` are loaded
- Copy `p_filesz` bytes from file offset `p_offset` to memory address `p_vaddr`
- If `p_memsz > p_filesz`, zero-fill the remaining bytes

---

### ELF Loading Sequence
1. Read and validate the ELF header
2. Seek to the program header table
3. For each program header:
   - Skip non-loadable segments
   - Copy segment data into memory
   - Zero-fill extra memory if required
4. Set the program counter to the ELF entry point

---



### Testing

- Dump the full 1 MiB emulator memory to a binary file
- Compare the dump against a flat binary
- All unused memory should be zeroed

---

### Key Notes
- Section headers are ignored
- Only program headers are used
- Only executable, 32-bit RISC-V ELF files are supported

## Project Structure
```bash
riscv_vm/
├── include/
│ ├── memory.hpp
│ ├── registers.hpp
│ ├── machine.hpp
| ├── elf_loader.hpp
│ └── utils.hpp
│
├── src/
│ ├── memory.cpp
│ ├── registers.cpp
│ ├── machine.cpp
│ ├── main.cpp
│ ├── test_machine.cpp
│ ├── test_elf.cpp
│ ├── elf_loader.cpp
|
├── Makefile
├── README.md
├── test_elf_output.txt
└── test_machine_output.txt

```

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
```
### Testing Machine For Grading
- remove test_elf.cpp from the make file
```bash
make clean
make
./riscv_vm > my_output.txt
diff my_output.txt test_machine_output.txt
```
### Testing ELF For Grading
- remove test_machine.cpp from the make file
```bash
make clean
make
./riscv_vm ./isaproject/tests/stdio.elf
hexdump -C memdump.bin > memdump.txt
diff memdump.txt test_elf_output.txt
```
### Example Out (Commented Out For Testing)
```bash
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
```
