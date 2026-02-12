#ifndef MACHINE_HPP
#define MACHINE_HPP

#include <cstdint>
#include <string>
#include "memory.hpp"
#include "register.hpp"

class Machine {

private:
    uint32_t pc;
    Register registers;
    Memory memory;

public:
    static constexpr uint32_t MEMORY_SIZE = 1 << 20; // 1 MiB

    // Constructor
    Machine();

    // Reset machine state
    void reset();

    // Memory access
    uint32_t readWord(uint32_t address) const;
    void writeWord(uint32_t address, uint32_t value);

    uint8_t readByte(uint32_t address) const;
    void writeByte(uint32_t address, uint8_t value);

    // Register access
    uint32_t readRegister(uint8_t reg) const;
    void writeRegister(uint8_t reg, uint32_t value);

    // Sign extension
    int32_t signExtend(uint32_t value, int bitWidth) const;

    // Debug
    void dump_memory_to_file(const std::string& filename) const ;

    // PC access
    uint32_t getPC() const;
    void setPC(uint32_t value);

    // Access full subsystems
    Register& getRegisters();
    Memory& getMemory();
};

#endif
