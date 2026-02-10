#include "register_file.hpp"

RegisterFile::RegisterFile(){

}

uint32_t RegisterFile::read(uint32_t index) const{
    if (index == 0)
        return 0;
    return reg[index];
}

void RegisterFile::write(uint32_t index, uint32_t value){
    
    if (index == 0)
        return;
    reg[index] = value;
    
}