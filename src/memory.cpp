#include "memory.hpp"
#include <iostream>

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
uint32_t Memory::readWord(uint32_t address) const
{
    return  static_cast<uint32_t>(data[address]) |
           (static_cast<uint32_t>(data[address + 1]) << 8) |
           (static_cast<uint32_t>(data[address + 2]) << 16) |
           (static_cast<uint32_t>(data[address + 3]) << 24);
}
void Memory::writeWord(uint32_t address, uint32_t value)
{
    data[address]     = static_cast<uint8_t>( value        & 0xFF);
    data[address + 1] = static_cast<uint8_t>((value >> 8)  & 0xFF);
    data[address + 2] = static_cast<uint8_t>((value >> 16) & 0xFF);
    data[address + 3] = static_cast<uint8_t>((value >> 24) & 0xFF);
}
void Memory::print(uint32_t start, uint32_t end) const {
std::cout << "MEMORY" << std::endl;
std::cout << "------" << std::endl;
for (uint32_t i = start; i < end; ++i) {
std::cout << std::hex << "mem[0x" << i << "]: 0x" <<
static_cast<int>(data[i]) << std::dec << std::endl;
}
}
std::vector<uint8_t>& Memory::getRawMemory()
{
    return data;
}

const std::vector<uint8_t>& Memory::getRawMemory() const
{
    return data;
}

