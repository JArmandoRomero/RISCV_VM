#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>
#include <vector>

class Memory {
private:
    std::vector<uint8_t> data;

public:
    explicit Memory(uint32_t size);

    // Byte access
    uint8_t read8(uint32_t address) const;
    void write8(uint32_t address, uint8_t value);

    // Word access (32-bit, little-endian)
    uint32_t readWord(uint32_t address) const;
    void writeWord(uint32_t address, uint32_t value);

    uint32_t size() const;
    void print(uint32_t start, uint32_t end) const;

    std::vector<uint8_t>& getRawMemory();
const std::vector<uint8_t>& getRawMemory() const;


};

#endif
