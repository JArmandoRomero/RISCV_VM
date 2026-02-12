#include "machine.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

// ANSI color codes
#define CLR_RESET   "\033[0m"
#define CLR_GREEN   "\033[32m"
#define CLR_CYAN    "\033[36m"
#define CLR_YELLOW  "\033[33m"
#define CLR_BOLD    "\033[1m"

// ---------------- Constructor ----------------

Machine::Machine()
    : pc(0),
      registers(),
      memory(MEMORY_SIZE)
{
    reset();

//     // -------- Fake boot delay --------
//     std::cout << CLR_CYAN << "Booting RISC-V VM";
//     for (int i = 0; i < 7; ++i) {
//         std::cout << "." << std::flush;
//         std::this_thread::sleep_for(std::chrono::milliseconds(300));
//     }
//     std::cout << CLR_RESET << "\n\n";

//     // ================= Boot Banner =================
//     std::cout << CLR_BOLD << CLR_GREEN;
//     std::cout << "          ██████╗ ██╗███████╗ ██████╗              ██╗   ██╗          \n";
//     std::cout << "          ██╔══██╗██║██╔════╝██╔════╝              ██║   ██║          \n";
//     std::cout << "          ██████╔╝██║███████╗██║         █████╗    ██║   ██║          \n";
//     std::cout << "          ██╔══██╗██║╚════██║██║         ╚════╝    ╚██╗ ██╔╝          \n";
//     std::cout << "          ██║  ██║██║███████║╚██████╗               ╚████╔╝           \n";
//     std::cout << "          ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝                ╚═══╝            \n";
//     std::cout << "                                                                      \n";
//     std::cout << "███████╗███╗   ███╗██╗   ██╗██╗      █████╗ ████████╗ ██████╗ ██████╗ \n";
//     std::cout << "██╔════╝████╗ ████║██║   ██║██║     ██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗\n";
//     std::cout << "█████╗  ██╔████╔██║██║   ██║██║     ███████║   ██║   ██║   ██║██████╔╝\n";
//     std::cout << "██╔══╝  ██║╚██╔╝██║██║   ██║██║     ██╔══██║   ██║   ██║   ██║██╔══██╗\n";
//     std::cout << "███████╗██║ ╚═╝ ██║╚██████╔╝███████╗██║  ██║   ██║   ╚██████╔╝██║  ██║\n";
//     std::cout << "╚══════╝╚═╝     ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝\n";
//     std::cout << "                            Jarrod Romero                             \n";
//     std::cout << "                               COSC 530                               \n";
//     std::cout << CLR_RESET << "\n";

//     std::cout << CLR_BOLD << CLR_GREEN
//               << "RISC-V Machine initialized"
//               << CLR_RESET << "\n";

//     std::cout << CLR_CYAN
//               << "Memory size: "
//               << CLR_RESET
//               << MEMORY_SIZE << " bytes (1 MiB)\n";

//     std::cout << CLR_CYAN
//               << "Stack Pointer (x2): "
//               << CLR_YELLOW << "0x"
//               << std::hex << MEMORY_SIZE
//               << std::dec << CLR_RESET << "\n";

//     std::cout << CLR_CYAN
//               << "Program Counter initialized to: "
//               << CLR_RESET
//               << pc << "\n\n";



//    // -------- Fake boot delay --------
//     std::cout << CLR_CYAN << "Testing Machine RISC-V VM";
//     for (int i = 0; i < 7; ++i) {
//         std::cout << "." << std::flush;
//         std::this_thread::sleep_for(std::chrono::milliseconds(300));
//     }
//     std::cout << CLR_RESET << "\n\n";




}


// ---------------- Reset ----------------

void Machine::reset()
{
    pc = 0;

    registers.reset();

    // Set stack pointer (x2)
    registers.write(2, MEMORY_SIZE);
}

// ---------------- Memory Access ----------------

uint32_t Machine::readWord(uint32_t address) const
{
    return memory.readWord(address);
}

void Machine::writeWord(uint32_t address, uint32_t value)
{
    memory.writeWord(address, value);
}

uint8_t Machine::readByte(uint32_t address) const
{
    return memory.read8(address);
}

void Machine::writeByte(uint32_t address, uint8_t value)
{
    memory.write8(address, value);
}

// ---------------- Register Access ----------------

uint32_t Machine::readRegister(uint8_t reg) const
{
    return registers.read(reg);
}

void Machine::writeRegister(uint8_t reg, uint32_t value)
{
    registers.write(reg, value);
}

// ---------------- Sign Extension ----------------

int32_t Machine::signExtend(uint32_t value, int bitWidth) const
{
    uint32_t mask = 1u << (bitWidth - 1);
    return (value ^ mask) - mask;
}

// ---------------- PC Access ----------------

uint32_t Machine::getPC() const
{
    return pc;
}

void Machine::setPC(uint32_t value)
{
    pc = value;
}

// ---------------- Subsystem Access ----------------

Register& Machine::getRegisters()
{
    return registers;
}

Memory& Machine::getMemory()
{
    return memory;
}

// ---------------- Dump Memory ----------------
void Machine::dump_memory_to_file(const std::string& filename) const {
std::ofstream outfile(filename, std::ios::binary);
if (!outfile) {
std::cerr << "Failed to open file for memory dump: " << filename <<
std::endl;
return;
}
const std::vector<uint8_t>& mem_data = memory.getRawMemory();
outfile.write(reinterpret_cast<const char*>(mem_data.data()), mem_data.size());
outfile.close();
std::cout << "Memory dumped to file: " << filename << std::endl;
}
