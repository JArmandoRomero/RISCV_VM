#include "elf_loader.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>

#define ELF_MAGIC_0 0x7F
#define ELF_MAGIC_1 'E'
#define ELF_MAGIC_2 'L'
#define ELF_MAGIC_3 'F'

#define ETYPE_EXEC 2
#define EMACHINE_RISCV 243
#define PT_LOAD 1

// 32-bit ELF Header (only required fields included)
struct ELF_Header {
    unsigned char e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint32_t e_entry;
    uint32_t e_phoff;
    uint32_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
};

// 32-bit Program Header
struct Program_Header {
    uint32_t p_type;
    uint32_t p_offset;
    uint32_t p_vaddr;
    uint32_t p_paddr;
    uint32_t p_filesz;
    uint32_t p_memsz;
    uint32_t p_flags;
    uint32_t p_align;
};

bool load_elf(const std::string& filename, Machine& machine)
{
    // 1️⃣ Open file
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file.\n";
        return false;
    }

    // 2️⃣ Read ELF header
    ELF_Header header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    // 3️⃣ Validate ELF magic
    if (header.e_ident[0] != ELF_MAGIC_0 ||
        header.e_ident[1] != ELF_MAGIC_1 ||
        header.e_ident[2] != ELF_MAGIC_2 ||
        header.e_ident[3] != ELF_MAGIC_3)
    {
        std::cerr << "Invalid ELF magic.\n";
        return false;
    }

    // 4️⃣ Validate executable type and architecture
    if (header.e_type != ETYPE_EXEC ||
        header.e_machine != EMACHINE_RISCV)
    {
        std::cerr << "Not a RISC-V executable.\n";
        return false;
    }

    // 5️⃣ Load each program header
    for (int i = 0; i < header.e_phnum; ++i)
    {
        // Move to correct program header location
        file.seekg(header.e_phoff + i * header.e_phentsize);

        Program_Header ph;
        file.read(reinterpret_cast<char*>(&ph), sizeof(ph));

        if (ph.p_type != PT_LOAD)
            continue;  // skip non-loadable segments

        // Read segment bytes from file
        std::vector<uint8_t> buffer(ph.p_filesz);
        file.seekg(ph.p_offset);
        file.read(reinterpret_cast<char*>(buffer.data()), ph.p_filesz);

        // Copy into emulator memory
        for (uint32_t j = 0; j < ph.p_filesz; ++j)
        {
            machine.writeByte(ph.p_vaddr + j, buffer[j]);
        }

        // Zero-fill remainder (BSS)
        for (uint32_t j = ph.p_filesz; j < ph.p_memsz; ++j)
        {
            machine.writeByte(ph.p_vaddr + j, 0);
        }
    }

    // 6️⃣ Set program counter
    machine.setPC(header.e_entry);

    return true;
}
