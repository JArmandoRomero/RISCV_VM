#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cstdint>

struct Instruction {

    uint32_t inst = 0;

    uint32_t left = 0;
    uint32_t right = 0;
    uint32_t result = 0;

    uint32_t disp = 0;

    uint8_t rd = 0;
    uint8_t memop = 0;
    uint8_t aluop = 0;
};

#endif