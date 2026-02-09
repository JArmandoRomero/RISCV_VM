#ifndef MACHINE_HPP
#define MACHINE_HPP

#include <cstdint>
#include "memory.hpp"
#include "register_file.hpp"

class Machine {
public:
    static constexpr uint32_t MEMORY_SIZE = 1 << 20; // 1 MiB

    Memory memory;
    RegisterFile regs;
    uint32_t pc;

    Machine();
};

#endif
