#include <iostream>
#include "register.hpp"
#include "memory_stage.hpp"
#include "memory.hpp"
#include "machine.hpp"
#include "instruction.hpp"
#include "elf_loader.hpp"
#include "fetch.hpp"
#include <iomanip>
#include <bitset>



// Helper to print the instruction structure
void print_instruction(const Instruction& instr) {
    std::cout << "Instruction:\n";
    std::cout << "  inst   = " << std::bitset<32>(instr.inst) << "\n";
    std::cout << "  rd     = " << static_cast<int>(instr.rd) << "\n";
    std::cout << "  memop  = " << std::bitset<3>(instr.memop) << "\n";
    std::cout << "  aluop  = " << static_cast<int>(instr.aluop) << "\n";
    std::cout << "  left   = " << instr.left << "\n";
    std::cout << "  right  = " << instr.right << "\n";
    std::cout << "  disp   = " << std::bitset<32>(instr.disp) << std::hex << " (0x" << instr.disp<< ")" <<"\n"; 
    std::cout << "  result = " << std::bitset<32>(instr.result) << std::hex << " (0x" << instr.result << ")" <<"\n";
    std::cout << std::endl;
}


void test_memory_stage(Machine& machine) {
    Instruction instr{};
    Memory& mem = machine.getMemory();

    std::cout << "\nTESTING MEMORY OPERATIONS\n";

    // Test No Op
    std::cout << "\nTest No Op\n";
    std::cout << "==========\n";

    instr.memop = 0b000;
    instr.result = 100;

    std::cout << "Before Op\n";
    mem.print(99, 105);
    print_instruction(instr);

    execute_memory(instr, machine);

    std::cout << "After Op\n";
    mem.print(99, 105);
    print_instruction(instr);


    // Test Store Byte
    std::cout << "\nTest Store Byte\n";
    std::cout << "==========\n";

    instr.memop = 0b101;
    instr.result = 100;
    instr.disp = 0xAB;

    std::cout << "Before Op\n";
    mem.print(99, 105);
    print_instruction(instr);

    execute_memory(instr, machine);

    std::cout << "After Op\n";
    mem.print(99, 105);
    print_instruction(instr);

    // Test Store Halfword
    std::cout << "\nTest Store Halfword\n";
    std::cout << "==========\n";

    instr.memop = 0b110;
    instr.result = 100;
    instr.disp = 0xCD;

    std::cout << "Before Op\n";
    mem.print(99, 105);
    print_instruction(instr);

    execute_memory(instr, machine);

    std::cout << "After Op\n";
    mem.print(99, 105);
    print_instruction(instr);

    // Test Store Word
    std::cout << "\nTest Store Word\n";
    std::cout << "==========\n";

    instr.memop = 0b111;
    instr.result = 100;
    instr.disp = 0xEF;

    std::cout << "Before Op\n";
    mem.print(99, 105);
    print_instruction(instr);

    execute_memory(instr, machine);

    std::cout << "After Op\n";
    mem.print(99, 105);
    print_instruction(instr);

    // Test Load Byte (Signed)
    std::cout << "\nTest Load Byte (Signed)\n";
    std::cout << "==========\n";

    instr.inst = 0; 
    instr.memop = 0b001;
    instr.result = 100;
    instr.disp = 0xEF;

    std::cout << "Before Op\n";
    mem.print(99, 105);
    print_instruction(instr);

    execute_memory(instr, machine);

    std::cout << "After Op\n";
    mem.print(99, 105);
    print_instruction(instr);

    // Test Load Byte (Unsigned)
    std::cout << "\nTest Load Byte (Unsigned)\n";
    std::cout << "==========\n";

    instr.inst = 0b00000000000000000100000000000000;
    instr.memop = 0b001;
    instr.result = 100;
    instr.disp = 0xEF;

    std::cout << "Before Op\n";
    mem.print(99, 105);
    print_instruction(instr);

    execute_memory(instr, machine);

    std::cout << "After Op\n";
    mem.print(99, 105);
    print_instruction(instr);

    // Test Load Halfword (Signed)
    std::cout << "\nTest Load Halfword (Signed)\n";
    std::cout << "==========\n";

    instr.inst = 0; 
    instr.memop = 0b010;
    instr.result = 100;
    instr.disp = 0xEF;
    mem.write8(101, 0xEF);

    std::cout << "Before Op\n";
    mem.print(99, 105);
    print_instruction(instr);

    execute_memory(instr, machine);

    std::cout << "After Op\n";
    mem.print(99, 105);
    print_instruction(instr);

    // Test Load Halfword (Unsigned)
    std::cout << "\nTest Load Halfword (Unsigned)\n";
    std::cout << "==========\n";

    instr.inst = 0b00000000000000000100000000000000;
    instr.memop = 0b010;
    instr.result = 100;
    instr.disp = 0xEF;
    mem.write8(101, 0xEF);

    std::cout << "Before Op\n";
    mem.print(99, 105);
    print_instruction(instr);

    execute_memory(instr, machine);

    std::cout << "After Op\n";
    mem.print(99, 105);
    print_instruction(instr);

    // Test Load Word
    std::cout << "\nTest Load Word\n";
    std::cout << "==========\n";

    instr.inst = 0; 
    instr.memop = 0b011;
    instr.result = 100;
    instr.disp = 0xEF;
    mem.write8(101, 0xEF);
    mem.write8(102, 0xCD);
    mem.write8(103, 0xAB);

    std::cout << "Before Op\n";
    mem.print(99, 105);
    print_instruction(instr);

    execute_memory(instr, machine);

    std::cout << "After Op\n";
    mem.print(99, 105);
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
    test_memory_stage(machine);

    return 0;
}
