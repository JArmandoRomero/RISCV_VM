#include "register.hpp"
#include <iostream>
#include <iomanip>

Register::Register()
{
    reset();
}

void Register::reset()
{
    for (int i = 0; i < 32; ++i)
        reg[i] = 0;
}

uint32_t Register::read(uint32_t index) const
{
    if (index == 0)
        return 0;

    return reg[index];
}

void Register::write(uint32_t index, uint32_t value)
{
    if (index == 0)
        return;

    reg[index] = value;
}

void Register::print() const
{
    std::cout << "REGISTERS\n";
    std::cout << "---------\n";

    for (int i = 0; i < 32; ++i)
    {
        std::cout << "x" << i << ": "
                  << read(i) << "\n";
    }

    std::cout << "---------\n";
}
