#include <iostream>

#include "register.hpp"
#include "memory.hpp"
#include "machine.hpp"
#include "elf_loader.hpp"
#include "fetch.hpp"
#include "decode.hpp"
#include <iomanip>
#include <bitset>




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


void test_decode() {
    std::cout << "\nTesting decode on blank Machine" << std::endl;
    Machine machine;

    // ==== TEST 1: R-type ====
    std::cout << "TEST 1: ADD x1, x2, x3\n";
    std::cout << "  Setup: x2 = 10, x3 = 20\n";
    machine.writeRegister(2, 10);
    machine.writeRegister(3, 20);
    Instruction instruction{};

    std::cout << "Expected Decoded Instruction:\n";
    std::cout << "  inst   = 00000000001100010000000010110011\n";
    std::cout << "  rd     = 1\n";
    std::cout << "  memop  = 0000\n";
    std::cout << "  aluop  = 1\n";  // Add operation
    std::cout << "  left   = 10\n";
    std::cout << "  right  = 20\n";
    std::cout << "  disp   = 0\n";
    std::cout << "  result = 0\n";
    std::cout << std::endl;


    uint32_t instr = 0b00000000001100010000000010110011;


    instruction.inst = instr;
    Instruction decoded = decode(instruction, &machine);
    print_instruction(decoded);
    machine.reset();

    // ==== TEST 2: I-type ====
    std::cout << "TEST 2: ADDI x5, x6, -1\n";
    std::cout << "  Setup: x6 = 100\n";
    machine.writeRegister(6, 100);

    std::cout << "Expected Decoded Instruction:\n";
    std::cout << "  inst   = 11111111111100110000001010010011\n";
    std::cout << "  rd     = 5\n";
    std::cout << "  memop  = 0000\n";
    std::cout << "  aluop  = 1\n";  // Add operation
    std::cout << "  left   = 100\n";
    std::cout << "  right  = -1\n";  // Sign-extended immediate
    std::cout << "  disp   = 0\n";
    std::cout << "  result = 0\n";
    std::cout << std::endl;

    // I-type: addi x5, x6, -1
    instr = 0b11111111111100110000001010010011;
    //             |  imm[11:0]   | rs1  |funct3| rd   | opcode|
    //             |111111111111  |00110 | 000  |00101 |0010011|
    // Values:     |    0xFFF     | 0x06 | 0x0  | 0x05 |  0x13 |

    instruction.inst = instr;
    decoded = decode(instruction, &machine);
    print_instruction(decoded);
    machine.reset();

    // ==== TEST 3: S-type ====
    std::cout << "TEST 3: SW x10, 8(x11)\n";
    std::cout << "  Setup: x10 = 0xDEADBEEF, x11 = 0x1000\n";
    machine.writeRegister(10, 0xDEADBEEF);  // Value to store
    machine.writeRegister(11, 0x1000);      // Base address

    std::cout << "Expected Decoded Instruction:\n";
    std::cout << "  inst   = 00000000101001011010010000100011\n";
    std::cout << "  rd     = 0\n";    // S-type has no rd
    std::cout << "  memop  = 0111\n"; // Store word (0b1XX with XX=11 for word)
    std::cout << "  aluop  = 1\n";    // Add operation (base + offset)
    std::cout << "  left   = 4096\n"; // x11 value (0x1000 = 4096)
    std::cout << "  right  = 8\n";    // Sign-extended offset
    std::cout << "  disp   = -559038737\n"; // strval = x10 value (0xDEADBEEF as signed)
    std::cout << "  result = 0\n";
    std::cout << std::endl;

    // S-type: sw x10, 8(x11)
    instr = 0b00000000101001011010010000100011;
    //             | imm[11:5] | rs2  | rs1  |funct3| imm[4:0] | opcode|
    //             |0000000    |01010 |01011 | 010  | 01000    |0100011|
    // Values:     |  0x00     | 0x0A | 0x0B | 0x2  |  0x08    |  0x23 |

    instruction.inst = instr;
    decoded = decode(instruction, &machine);
    print_instruction(decoded);
    machine.reset();

    // ==== TEST 4: B-type ====
    std::cout << "TEST 4: BEQ x1, x2, 16\n";
    std::cout << "  Setup: x1 = 42, x2 = 42\n";
    machine.writeRegister(1, 42);
    machine.writeRegister(2, 42);

    std::cout << "Expected Decoded Instruction:\n";
    std::cout << "  inst   = 00000000001000001000100001100011\n";
    std::cout << "  rd     = 0\n";    // B-type has no rd
    std::cout << "  memop  = 0000\n";
    std::cout << "  aluop  = 16\n";   // Cmp operation
    std::cout << "  left   = 42\n";
    std::cout << "  right  = 42\n";
    std::cout << "  disp   = 16\n";   // Branch displacement
    std::cout << "  result = 0\n";
    std::cout << std::endl;

    // B-type: beq x1, x2, 16
    instr = 0b00000000001000001000100001100011;
    //           |imm[12]|imm[10:5]| rs2 | rs1 |funct3|imm[4:1]|imm[11]|opcode |
    //           |   0   | 000000  |00010|00001| 000  | 1000   |   0   |1100011|
    // Values:   | 0x0   |  0x00   | 0x2 | 0x1 | 0x0  | 0x8    | 0x0   |  0x63 |
    // Displacement: imm[12:1] = 0000000010000 = 16

    instruction.inst = instr;
    decoded = decode(instruction, &machine);
    print_instruction(decoded);
    machine.reset();

    // ==== TEST 5: U-type ====
    std::cout << "TEST 5: LUI x4, 0x12345\n";
    std::cout << "  Setup: (no register setup needed)\n";

    std::cout << "Expected Decoded Instruction:\n";
    std::cout << "  inst   = 00010010001101000101001000110111\n";
    std::cout << "  rd     = 4\n";
    std::cout << "  memop  = 0000\n";
    std::cout << "  aluop  = 1\n";    // Add operation
    std::cout << "  left   = 0\n";    // LUI adds to 0
    std::cout << "  right  = 305418240\n"; // 0x12345000 (upper immediate shifted left 12 bits (3 zeros in hex))
    std::cout << "  disp   = 0\n";
    std::cout << "  result = 0\n";
    std::cout << std::endl;

    // U-type: lui x4, 0x12345
    instr = 0b00010010001101000101001000110111;
    //             |         imm[31:12]          |  rd  | opcode|
    //             |00010010001101000101         |00100 |0110111|
    // Values:     |         0x12345             | 0x04 |  0x37 |

    instruction.inst = instr;
    decoded = decode(instruction, &machine);
    print_instruction(decoded);
    machine.reset();

    // ==== TEST 6: J-type ====
    std::cout << "TEST 6: JAL x1, 2048\n";
    std::cout << "  Setup: (no register setup needed)\n";

    std::cout << "Expected Decoded Instruction:\n";
    std::cout << "  inst   = 00000000000100000000000011101111\n";
    std::cout << "  rd     = 1\n";    
    std::cout << "  memop  = 0000\n";
    std::cout << "  aluop  = 0\n";    // Nop (ALU not used for JAL)
    std::cout << "  left   = 0\n";
    std::cout << "  right  = 0\n";
    std::cout << "  disp   = 2048\n"; // Jump displacement
    std::cout << "  result = 0\n";
    std::cout << std::endl;

    // J-type: jal x1, 2048
    instr = 0b00000000000100000000000011101111;
    //             | imm[20]|imm[10:1] |imm[11]|imm[19:12]| rd   | opcode|
    //             |   0    |0000000000|   1   |00000000  |00001 |1101111|
    // Values:     | 0x0    |  0x0     | 0x1   |  0x00    | 0x01 |  0x6F |
    // Displacement: imm[20:1] = 00000000100000000000 = 2048

    instruction.inst = instr;
    decoded = decode(instruction, &machine);
    print_instruction(decoded);
    machine.reset();
}


int main()
{
    test_decode();

    return 0;
}

