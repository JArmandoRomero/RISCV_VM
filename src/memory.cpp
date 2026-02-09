#include "memory.hpp"

Memory::Memory(uint32_t size)
    : data(size) {
   
}

uint8_t Memory::read8(uint32_t address) const {
    return data[address];
}

void Memory::write8(uint32_t address, uint8_t value) {
    data[address] = value;
}

uint32_t Memory::size() const {
    return data.size();
}
