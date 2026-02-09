#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>
#include <vector>

class Memory {
private:
    std::vector<uint8_t> data;

public:
    explicit Memory(uint32_t size);

    uint8_t read8(uint32_t address) const;
    void write8(uint32_t address, uint8_t value);

    uint32_t size() const;
};

#endif
