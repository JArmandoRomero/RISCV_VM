#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cstdint>

struct Instruction {

    int32_t inst = 0;

    int32_t left = 0;
    int32_t right = 0;
    int32_t result = 0;

    int32_t disp = 0;

    uint8_t rd = 0;
    uint8_t memop = 0;
    uint8_t aluop = 0;
};

#endif