#include <iostream>
#include "register.hpp"
#include "memory.hpp"
#include "machine.hpp"
#include "instruction.hpp"
#include "elf_loader.hpp"
#include "fetch.hpp"
#include "writeback.hpp"
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
    std::cout << "  disp   = " << std::dec << instr.disp << " (0b" << std::bitset<32>(instr.disp) << ", " << std::hex << "0x" << instr.disp<< ")" <<"\n"; 
    std::cout << "  result = " << std::dec << instr.result << " (0b" << std::bitset<32>(instr.result) << ", " << std::hex << "0x" << instr.result<< ")" <<"\n"; 
    std::cout << std::endl;
}

// Helper to print PC
void print_pc(Machine& machine) {
    std::cout << std::dec
          << "PC: "
          << machine.getPC() 
          << " (0x"
          << std::hex << std::uppercase
          << machine.getPC() 
          << std::dec
          << ")"
          << std::endl;
}


void test_writeback(Machine& machine) {
    Instruction instr{};
    Register& regs = machine.getRegisters();

    machine.setPC(82);

    std::cout << "\nTESTING WRITEBACK OPERATIONS\n";

    // Test System Instructions
    std::cout << "\nTest System Instructions\n";
    std::cout << "==========\n";
    instr.inst = 0b00000000000000000000000001110011;
    // Test exit
    std::cout << "\nTest Exit\n";
    instr.result = 0;
    instr.rd = 0;
    
    machine.writeRegister(17, 0); // x17 should get 0
    machine.writeRegister(10, 3); // Made up exit code
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);
    std::cout << "Machine Is Running: " << machine.is_running << "\n";

    writeback(instr, machine);

    std::cout << "After Op\n";
    print_pc(machine);
    std::cout << "Machine Is Running: " << machine.is_running << "\n";
    std::cout << "Exit Code: " << machine.exit_code << "\n";

    // Test putchar
    std::cout << "\nTest Putchar\n";
    machine.writeRegister(17, 1); // x17 should get 1
    machine.writeRegister(10, 0b01000001); // Binary encoding of "A" 
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    std::cout << "\nOutput of Op: ";
    writeback(instr, machine);

    std::cout << "\nAfter Op\n";
    print_pc(machine);

    // Test getchar
    std::cout << "\nTest Getchar\n";
    machine.writeRegister(17, 2); // x17 should get 2
    machine.writeRegister(10, 0);
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "\nAfter Op\n";
    regs.print();
    print_pc(machine);
    // Test debug
    std::cout << "\nTest Debug\n";
    machine.writeRegister(17, 3); // x17 should get 3
    machine.writeRegister(10, 0);
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "\nAfter Op\n";
    regs.print();
    print_pc(machine);

    // Test Standard Operation 
    instr.result = 100;
    instr.rd = 10;
    instr.inst = 0b00000000000000000000000000010011;

    std::cout << "\nTest Standard Operation\n";
    std::cout << "==========\n";
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "After Op\n";
    regs.print();
    print_pc(machine);

    // Test JAL
    instr.inst = 0b00000000000000000000000001101111;
    instr.disp = 32;
    instr.rd = 11;
    instr.result = 0;


    std::cout << "\n\nTest JAL\n";
    std::cout << "==========\n";
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "After Op\n";
    regs.print();
    print_pc(machine);

    // Test JALR
    // Test Case 1
    instr.inst = 0b00000000000000000000000001100111;
    instr.disp = 0;
    instr.rd = 11;
    instr.result = 33;


    std::cout << "\n\nTest JALR\n";
    std::cout << "==========\n";
    std::cout << "Test Case 1 (odd result)\n";
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "After Op\n";
    regs.print();
    print_pc(machine);

    // Test Case 2
    instr.inst = 0b00000000000000000000000001100111;
    instr.disp = 0;
    instr.rd = 11;
    instr.result = 42;


    std::cout << "\n\nTest JALR\n";
    std::cout << "==========\n";
    std::cout << "Test Case 2 (even result)\n";
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "After Op\n";
    regs.print();
    print_pc(machine);

    // Test BEQ
    // Test Branch Taken 
    instr.inst = 0b00000000000000000000000001100011;
    instr.disp = 32;
    instr.rd = 0;
    instr.result = 0b001;


    std::cout << "\n\nTest BEQ (Test Branch Taken)\n";
    std::cout << "==========\n";
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "After Op\n";
    regs.print();
    print_pc(machine);
    // Test Branch Not Taken 
    instr.disp = 32;
    instr.rd = 0;
    instr.result = 0b000;


    std::cout << "\n\nTest BEQ (Test Branch Not Taken)\n";
    std::cout << "==========\n";
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "After Op\n";
    regs.print();
    print_pc(machine);

    // Test BNE
    instr.inst = 0b00000000000000000001000001100011;
    // Test Branch Taken 
    instr.disp = 32;
    instr.rd = 0;
    instr.result = 0b000;


    std::cout << "\n\nTest BNE (Test Branch Taken)\n";
    std::cout << "==========\n";
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "After Op\n";
    regs.print();
    print_pc(machine);
    // Test Branch Not Taken 
    instr.disp = 32;
    instr.rd = 0;
    instr.result = 0b001;


    std::cout << "\n\nTest BNE (Test Branch Not Taken)\n";
    std::cout << "==========\n";
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "After Op\n";
    regs.print();
    print_pc(machine);
    // Test BLT
    instr.inst = 0b00000000000000000100000001100011;
    // Test Branch Taken 
    instr.disp = 32;
    instr.rd = 0;
    instr.result = 0b010;


    std::cout << "\n\nTest BLT (Test Branch Taken)\n";
    std::cout << "==========\n";
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "After Op\n";
    regs.print();
    print_pc(machine);
    // Test Branch Not Taken 
    instr.disp = 32;
    instr.rd = 0;
    instr.result = 0b000;


    std::cout << "\n\nTest BLT (Test Branch Not Taken)\n";
    std::cout << "==========\n";
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "After Op\n";
    regs.print();
    print_pc(machine);
    // Test BGE
    instr.inst = 0b00000000000000000101000001100011;
    // Test Branch Taken 
    instr.disp = 32;
    instr.rd = 0;
    instr.result = 0b000;


    std::cout << "\n\nTest BGE (Test Branch Taken)\n";
    std::cout << "==========\n";
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "After Op\n";
    regs.print();
    print_pc(machine);
    // Test Branch Not Taken 
    instr.disp = 32;
    instr.rd = 0;
    instr.result = 0b010;


    std::cout << "\n\nTest BGE (Test Branch Not Taken)\n";
    std::cout << "==========\n";
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "After Op\n";
    regs.print();
    print_pc(machine);
    // Test BLTU
    instr.inst = 0b00000000000000000110000001100011;
    // Test Branch Taken 
    instr.disp = 32;
    instr.rd = 0;
    instr.result = 0b100;


    std::cout << "\n\nTest BLTU (Test Branch Taken)\n";
    std::cout << "==========\n";
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "After Op\n";
    regs.print();
    print_pc(machine);
    // Test Branch Not Taken 
    instr.disp = 32;
    instr.rd = 0;
    instr.result = 0b000;


    std::cout << "\n\nTest BLTU (Test Branch Not Taken)\n";
    std::cout << "==========\n";
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "After Op\n";
    regs.print();
    print_pc(machine);
    // Test BGEU
    instr.inst = 0b00000000000000000111000001100011;
    // Test Branch Taken 
    instr.disp = 32;
    instr.rd = 0;
    instr.result = 0b000;


    std::cout << "\n\nTest BGEU (Test Branch Taken)\n";
    std::cout << "==========\n";
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "After Op\n";
    regs.print();
    print_pc(machine);
    // Test Branch Not Taken 
    instr.disp = 32;
    instr.rd = 0;
    instr.result = 0b100;


    std::cout << "\n\nTest BGEU (Test Branch Not Taken)\n";
    std::cout << "==========\n";
    std::cout << "Before Op\n";
    print_instruction(instr);
    regs.print();
    print_pc(machine);

    writeback(instr, machine);

    std::cout << "After Op\n";
    regs.print();
    print_pc(machine);

    return;
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <elf_file>" << std::endl;
        return 1;
    }

    std::string elf_filename = argv[1];
    Machine machine;

    test_writeback(machine);

    return 0;
}
