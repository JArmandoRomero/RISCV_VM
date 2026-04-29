#include "writeback.hpp"
#include <iostream>

void writeback(Instruction& instr, Machine& machine)
{
    uint32_t pc = machine.getPC();
    uint32_t next_pc = pc + 4;

    uint32_t opcode = instr.inst & 0x7F;

    // =========================
    // SYSTEM CALL (ECALL)
    // =========================
    if (opcode == 0b1110011)
    {
        uint32_t syscall = machine.readRegister(17); // a7

        switch (syscall)
        {
            case 0: // exit
                machine.exit_code = machine.readRegister(10);
                machine.is_running = false;
                return;

            case 1: // putchar
                std::cout << static_cast<char>(machine.readRegister(10));
                break;

            case 2: { // getchar
                char c;
                std::cin.get(c);
                machine.writeRegister(10, static_cast<uint32_t>(c));
                break;
            }

            case 3: // debug
                machine.getRegisters().print();
                break;
        }
    }

    // =========================
    // WRITE TO REGISTER
    // =========================
    if (instr.rd != 0) {
        machine.writeRegister(instr.rd, instr.result);
    }

    // =========================
    // PROGRAM COUNTER UPDATE
    // =========================

    // JAL
    if (opcode == 0b1101111) {
        next_pc = pc + instr.disp;
    }

    // JALR
    else if (opcode == 0b1100111) {
        next_pc = instr.result & ~1; // clear LSB
    }

    // Branch (B-type)
    else if (opcode == 0b1100011) {
        if (instr.result != 0) {
            next_pc = pc + instr.disp;
        }
    }

    machine.setPC(next_pc);
}