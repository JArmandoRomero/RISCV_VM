#include "fetch.hpp"

void fetch(Machine& machine, Instruction& instr)
{
    uint32_t pc = machine.getPC();

    // read 4 bytes (little endian)
    instr.inst = machine.readWord(pc);

    // advance program counter
    machine.setPC(pc + 4);
}