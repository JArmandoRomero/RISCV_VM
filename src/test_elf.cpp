#include <iostream>

#include "register.hpp"
#include "memory.hpp"
#include "machine.hpp"
#include "elf_loader.hpp"
#include <iomanip>
#include <bitset>


void test_elf(Machine& machine, std::string elf_filename) {
    if (!loadELF(elf_filename, machine)) {
        std::cerr << "Failed to load ELF file: " << elf_filename << std::endl;
        return;
    }

    std::cout << "ELF file loaded successfully." << std::endl;

    // Optional: print initial PC or memory region
    std::cout << "Initial PC: 0x" << std::hex << machine.getPC() << std::dec << std::endl;


    machine.dump_memory_to_file("memdump.bin");
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <elf_file>" << std::endl;
        return 1;
    }

    std::string elf_filename = argv[1];
    Machine machine;


    test_elf(machine, elf_filename);

    return 0;
}
