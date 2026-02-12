#include <iostream>

#include "register.hpp"
#include "memory.hpp"
#include "machine.hpp"
#include <iomanip>
#include <bitset>


void test_registers() {
    Register regs;

    // Read from register 4 and print
    std::cout << "Test Reading Value From Empty Register:" << std::endl;
    uint32_t value = regs.read(4);
    std::cout << "Value in x4: " << value << std::endl;

    // Write a value to register 5
    std::cout << "Test Writing Value To Register:" << std::endl;
    std::cout << "Write value 42 to register 5." << std::endl;
    regs.write(5, 42);

    // Read from register 5 and print
    std::cout << "Test Reading From Written To Register:" << std::endl;
    value = regs.read(5);
    std::cout << "Value in x5: " << value << std::endl;

    // Attempt to write to x0 (should have no effect)
    std::cout << "Test Writing To Zero Register:" << std::endl;
    std::cout << "Write value 99 to register 0." << std::endl;
    regs.write(0, 99);
    std::cout << "Value in x0 (should still be 0): " << regs.read(0) << std::endl;

    // Print all register values
    std::cout << "Print All Registers:" << std::endl;
    regs.print();
}

void test_memory() {
    Memory mem(1024 * 1024);

    std::cout << "Test Reading And Writing Byte To Memory:" << std::endl;
    std::cout << "Write value 0xAB to location 100." << std::endl;

    mem.write8(100, 0xAB);
    uint8_t byte_val = mem.read8(100);

    std::cout << "Byte at 100: 0x"
              << std::hex << static_cast<int>(byte_val)
              << std::dec << std::endl;

    std::cout << "Test Reading And Writing Word To Memory:" << std::endl;
    std::cout << "Write value 0x12345678 to location 104." << std::endl;

    mem.writeWord(104, 0x12345678);
    uint32_t word_val = mem.readWord(104);

    std::cout << "Word at 104: 0x"
              << std::hex << word_val
              << std::dec << std::endl;

    std::cout << "Test Overwriting In Memory:" << std::endl;
    std::cout << "Write value 0x87654321 to location 104." << std::endl;

    mem.writeWord(104, 0x87654321);
    word_val = mem.readWord(104);

    std::cout << "Word at 104 after overwrite: 0x"
              << std::hex << word_val
              << std::dec << std::endl;

    std::cout << "Memory dump from 100 to 108:" << std::endl;
    mem.print(100, 108);
}


int main(int argc, char* argv[]) {
    Machine machine;


    test_registers();
    test_memory();

    return 0;
}
