#include <iostream>
#include "instruction.hpp"
#include "register.hpp"
#include "memory.hpp"
#include "machine.hpp"
#include "elf_loader.hpp"
#include "fetch.hpp"
#include <iomanip>
#include <bitset>



// Helper to print the decoded instruction structure
void print_instruction(const Instruction& instr) {
    std::cout << "Decoded Instruction:\n";
    std::cout << "  inst   = " << std::bitset<32>(instr.inst) << "\n";
    std::cout << "  rd     = " << static_cast<int>(instr.rd) << "\n";
    std::cout << "  memop  = " << std::bitset<4>(instr.memop) << "\n";
    std::cout << "  aluop  = " << static_cast<int>(instr.aluop) << "\n";
    std::cout << "  left   = " << instr.left << "\n";
    std::cout << "  right  = " << instr.right << "\n";
    std::cout << "  disp   = " << instr.disp << "\n";
    std::cout << "  result = " << instr.result << "\n";
    std::cout << std::endl;
}


void test_fetch(Machine& machine) {
    Instruction instr ;
     fetch(machine, instr);

    std::cout << "Fetched instruction: 0x"
              << std::hex << instr.inst << std::dec << std::endl;
    print_instruction(instr);
}


void test_elf(Machine& machine, std::string elf_filename) {
    if (!load_elf(elf_filename, machine)) {
        std::cerr << "Failed to load ELF file: " << elf_filename << std::endl;
        return;
    }

    std::cout << "ELF file loaded successfully." << std::endl;
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <elf_file>" << std::endl;
        return 1;
    }

    std::string elf_filename = argv[1];
    Machine machine;


    test_elf(machine, elf_filename);
    test_fetch(machine);

    return 0;
}
