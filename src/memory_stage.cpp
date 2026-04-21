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
    Memory& mem = machine.getMemory();
    uint32_t addr = instr.result;

    switch (instr.memop) {

        // NO OP
        case 0b000:
            break;

        // LOAD BYTE
        case 0b001: {
            uint8_t val = mem.read8(addr);

            bool is_unsigned = (instr.inst >> 14) & 1;

            if (is_unsigned) {
                instr.result = val;
            } else {
                instr.result = static_cast<int8_t>(val); // sign extend
            }
            break;
        }

        // LOAD HALFWORD
        case 0b010: {
            uint16_t val = mem.read8(addr) |
                          (mem.read8(addr + 1) << 8);

            bool is_unsigned = (instr.inst >> 14) & 1;

            if (is_unsigned) {
                instr.result = val;
            } else {
                instr.result = static_cast<int16_t>(val); // sign extend
            }
            break;
        }

        // LOAD WORD
        case 0b011: {
            instr.result = mem.readWord(addr);
            break;
        }

        // STORE BYTE
        case 0b101: {
            mem.write8(addr, static_cast<uint8_t>(instr.disp));
            break;
        }

        // STORE HALFWORD
        case 0b110: {
            mem.write8(addr,     instr.disp & 0xFF);
            mem.write8(addr + 1, (instr.disp >> 8) & 0xFF);
            break;
        }

        // STORE WORD
        case 0b111: {
            mem.writeWord(addr, instr.disp);
            break;
        }
    }
}