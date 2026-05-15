# RISC-V RV32IM Virtual Machine

COSC 530 – Computer Architecture  
Author: Jarrod Romero

---

# Overview

This project implements a full **RISC-V RV32IM Virtual Machine (VM)** in modern C++. The emulator models the core hardware and execution pipeline of a simplified 32-bit RISC-V processor, including:

- Memory
- Registers
- Program Counter
- ELF Loading
- Instruction Fetching
- Instruction Decoding
- ALU Execution
- Memory Access
- Writeback Stage
- System Calls

The VM is developed incrementally as part of a multi-stage computer architecture project for COSC 530.

---

# Supported ISA

The emulator supports the **RV32IM** instruction set:

- **RV32I** → Base integer instruction set
- **M Extension** → Integer multiplication/division instructions

Supported instruction categories include:

- R-Type
- I-Type
- S-Type
- B-Type
- U-Type
- J-Type

---

# Implemented Features

## Machine Architecture

- 32-bit RISC-V CPU
- 32 general-purpose registers (`x0`–`x31`)
- Separate Program Counter (`PC`)
- 1 MiB byte-addressable RAM
- Stack pointer initialized according to RISC-V ABI
- Little-endian memory layout

---

## Register File

The emulator implements a complete RISC-V register file.

### Features

- 32 × 32-bit registers
- `x0` is hardwired to zero
- Writes to `x0` are ignored
- Supports:
  - `read()`
  - `write()`
  - `reset()`
  - `print()`

### ABI Support

| Register | ABI Name | Purpose |
|---|---|---|
| x0 | zero | Constant 0 |
| x1 | ra | Return address |
| x2 | sp | Stack pointer |
| x10-x17 | a0-a7 | Function/System call args |

---

# Memory System

## Features

- 1 MiB RAM
- Byte-addressable
- Little-endian word storage
- Bounds-checked access

## Supported Operations

- `read8()`
- `write8()`
- `readWord()`
- `writeWord()`
- `print()`
- `getRawMemory()`

---

# Machine Class

The `Machine` class represents the entire virtual CPU state.

## Responsibilities

- Owns memory
- Owns register file
- Maintains program counter
- Provides read/write helpers
- Handles reset logic
- Initializes stack pointer

---

# Boot System

The VM includes an optional boot interface featuring:

- ASCII boot banner
- ANSI colorized output
- Simulated boot delay
- Debug initialization information

These features are disabled during grading/testing to ensure output consistency.

---

# ELF Loader

The emulator supports loading executable **ELF (Executable and Linkable Format)** files.

## Supported ELF Constraints

| Feature | Value |
|---|---|
| Architecture | RISC-V |
| Bit Width | 32-bit |
| Endianness | Little-endian |
| File Type | Executable ELF |
| Machine ID | 243 |

---

## ELF Validation

The loader validates:

- ELF magic bytes
- RISC-V architecture
- 32-bit format
- Executable type

---

## ELF Loading Process

1. Read ELF header
2. Validate file format
3. Read program headers
4. Load PT_LOAD segments into memory
5. Zero-fill unused memory
6. Set PC to ELF entry point

---

# Pipeline Stages

The emulator implements a simplified RISC-V instruction pipeline.

---

## 1. Fetch Stage

The fetch stage:

- Reads 4 bytes from memory
- Uses little-endian assembly
- Loads instruction at current PC
- Stores result in `Instruction.inst`

---

## 2. Decode Stage

The decode stage:

- Determines instruction type
- Extracts:
  - opcode
  - funct3
  - funct7
  - rs1
  - rs2
  - rd
  - immediates
- Loads operands
- Selects ALU operation
- Handles sign extension

### Supported Decode Types

| Type | Purpose |
|---|---|
| R | Register arithmetic |
| I | Immediate arithmetic/load |
| S | Store |
| B | Branch |
| U | Upper immediate |
| J | Jump |

---

## 3. Execute Stage

The execute stage performs ALU operations.

### Supported ALU Operations

| Operation | Description |
|---|---|
| Add | Signed addition |
| Sub | Signed subtraction |
| Mul | Signed multiplication |
| Div | Signed division |
| DivU | Unsigned division |
| Rem | Signed remainder |
| RemU | Unsigned remainder |
| LeftShift | Logical left shift |
| RightShiftA | Arithmetic right shift |
| RightShiftL | Logical right shift |
| And | Bitwise AND |
| Or | Bitwise OR |
| Xor | Bitwise XOR |
| Slt | Signed less-than |
| SltU | Unsigned less-than |
| Cmp | Branch comparison |

---

## 4. Memory Stage

Handles:

- Loads
- Stores
- Byte access
- Word access

Supported memory instructions:

- LB
- LH
- LW
- LBU
- LHU
- SB
- SH
- SW

---

## 5. Writeback Stage

The writeback stage:

- Writes ALU results to registers
- Updates the PC
- Handles branch decisions
- Executes system calls

---

# System Calls

The emulator supports a basic syscall interface.

| Syscall | a7 | Description |
|---|---|---|
| exit | 0 | Exit VM |
| putchar | 1 | Print character |
| getchar | 2 | Read character |
| debug | 3 | Debug output |

---

# Instruction Structure

```cpp
struct Instruction {

    uint32_t inst = 0;

    int32_t left = 0;
    int32_t right = 0;
    int32_t result = 0;

    int32_t disp = 0;

    uint8_t rd = 0;
    uint8_t memop = 0;
    uint8_t aluop = 0;
};
```

---

# Project Structure

```bash
riscv_vm/
├── include/
│   ├── alu.hpp
│   ├── decode.hpp
│   ├── elf_loader.hpp
│   ├── execute.hpp
│   ├── fetch.hpp
│   ├── instruction.hpp
│   ├── machine.hpp
│   ├── memory.hpp
│   ├── register.hpp
│   ├── utils.hpp
│   └── writeback.hpp
│
├── src/
│   ├── decode.cpp
│   ├── elf_loader.cpp
│   ├── execute.cpp
│   ├── fetch.cpp
│   ├── machine.cpp
│   ├── memory.cpp
│   ├── register.cpp
│   ├── writeback.cpp
│   ├── test_machine.cpp
│   ├── test_elf.cpp
│   ├── test_fetch.cpp
│   ├── test_decode.cpp
│   └── main.cpp
│
├── Makefile
├── README.md
├── test_machine_output.txt
└── test_elf_output.txt
```

---

# Building the Project

## Requirements

- C++17 compatible compiler
- Linux / WSL / MSCS VM
- GNU Make

---

## Build Instructions

```bash
make clean
make
```

---

# Running the Emulator

## Run Machine Tests

```bash
./riscv_vm
```

---

## Run ELF Program

```bash
./riscv_vm program.elf
```

---

# Testing

## Machine Test

```bash
./riscv_vm > my_output.txt
diff my_output.txt test_machine_output.txt
```

---

## ELF Loader Test

```bash
./riscv_vm ./isaproject/tests/stdio.elf

hexdump -C memdump.bin > memdump.txt

diff memdump.txt test_elf_output.txt
```

---

# Design Goals

This project emphasizes:

- Clean modular architecture
- Accurate RISC-V behavior
- Incremental pipeline development
- Separation of hardware stages
- Modern C++ design
- Low-level systems programming concepts

---

# Key Computer Architecture Concepts

This emulator demonstrates:

- ISA implementation
- Fetch-decode-execute cycle
- Little-endian memory systems
- Register architecture
- Branch control flow
- Program loading
- ELF executable structure
- System call interfaces
- ALU design
- Sign extension
- Memory alignment

---

# Future Improvements

Potential future extensions include:

- Full RV32I coverage
- Pipeline hazards
- Branch prediction
- Instruction cache
- Data cache
- Virtual memory
- CSR support
- Floating-point extension
- Interactive debugger
- Disassembler
- Cycle counting
- Performance metrics

---

# References

- RISC-V Unprivileged ISA Specification
- ELF Specification
- COSC 530 Course Materials
- GNU Binutils
- RISC-V ABI Documentation

---

# Author

Jarrod Romero  
COSC 530 – Computer Architecture
