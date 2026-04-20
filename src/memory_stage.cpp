#include "memory_stage.hpp"
#include <cstdint>

// You can define this if not already defined elsewhere
enum MemOp {
    None,
    LB, LH, LW,
    LBU, LHU,
    SB, SH, SW
};

void execute_memory(Instruction& instr, Machine& machine) {
    uint32_t addr = instr.result;

    switch (instr.memop) {

        // =====================
        // STORE
        // =====================

        case SB:
            machine.writeByte(addr, instr.strval & 0xFF);
            break;

        case SH:
            machine.writeByte(addr, instr.strval & 0xFF);
            machine.writeByte(addr + 1, (instr.strval >> 8) & 0xFF);
            break;

        case SW:
            machine.writeWord(addr, instr.strval);
            break;

        // =====================
        // LOAD
        // =====================

        case LB: {
            int8_t val = machine.readByte(addr);
            instr.result = val;  // sign-extended
            break;
        }

        case LH: {
            int16_t val =
                machine.readByte(addr) |
                (machine.readByte(addr + 1) << 8);
            instr.result = val;
            break;
        }

        case LW:
            instr.result = machine.readWord(addr);
            break;

        case LBU: {
            uint8_t val = machine.readByte(addr);
            instr.result = val;  // zero-extended
            break;
        }

        case LHU: {
            uint16_t val =
                machine.readByte(addr) |
                (machine.readByte(addr + 1) << 8);
            instr.result = val;
            break;
        }

        default:
            // No memory operation
            break;
    }
}