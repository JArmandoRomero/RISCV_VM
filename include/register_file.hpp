#ifndef REGISTERS_HPP
#define REGISTERS_HPP


#include <cstdint>

class RegisterFile{

    private:
        uint32_t reg[32];

    public:
        RegisterFile();
        uint32_t read(uint32_t index) const;
        void write(uint32_t index, uint32_t value);
};

#endif
