#include "machine.hpp"
#include <iostream>
#include <thread>
#include <chrono>

// ANSI color codes
#define CLR_RESET   "\033[0m"
#define CLR_GREEN   "\033[32m"
#define CLR_CYAN    "\033[36m"
#define CLR_YELLOW  "\033[33m"
#define CLR_BOLD    "\033[1m"

Machine::Machine()
    : memory(MEMORY_SIZE),
      pc(0)
{
    // Initialize stack pointer (x2) to top of memory
    regs.write(2, MEMORY_SIZE);

    // -------- Fake boot delay --------
    std::cout << CLR_CYAN << "Booting RISC-V VM";
    for (int i = 0; i < 7; ++i) {
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    std::cout << CLR_RESET << "\n\n";
    // --------------------------------

    // ================= Boot Banner =================
 std::cout << CLR_BOLD << CLR_GREEN;
    std::cout << "          ██████╗ ██╗███████╗ ██████╗              ██╗   ██╗          \n";
    std::cout << "          ██╔══██╗██║██╔════╝██╔════╝              ██║   ██║          \n";
    std::cout << "          ██████╔╝██║███████╗██║         █████╗    ██║   ██║          \n";
    std::cout << "          ██╔══██╗██║╚════██║██║         ╚════╝    ╚██╗ ██╔╝          \n";
    std::cout << "          ██║  ██║██║███████║╚██████╗               ╚████╔╝           \n";
    std::cout << "          ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝                ╚═══╝            \n";
    std::cout << "                                                                      \n";
    std::cout << "███████╗███╗   ███╗██╗   ██╗██╗      █████╗ ████████╗ ██████╗ ██████╗ \n";
    std::cout << "██╔════╝████╗ ████║██║   ██║██║     ██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗\n";
    std::cout << "█████╗  ██╔████╔██║██║   ██║██║     ███████║   ██║   ██║   ██║██████╔╝\n";
    std::cout << "██╔══╝  ██║╚██╔╝██║██║   ██║██║     ██╔══██║   ██║   ██║   ██║██╔══██╗\n";
    std::cout << "███████╗██║ ╚═╝ ██║╚██████╔╝███████╗██║  ██║   ██║   ╚██████╔╝██║  ██║\n";
    std::cout << "╚══════╝╚═╝     ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝\n";
    std::cout << "                            Jarrod Romero                             \n";
    std::cout << "                               COSC 530                               \n";
    std::cout << CLR_RESET << "\n";
    // ===============================================

    std::cout << CLR_BOLD << CLR_GREEN
              << "RISC-V Machine initialized"
              << CLR_RESET << "\n";

    std::cout << CLR_CYAN
              << "Memory size: "
              << CLR_RESET
              << MEMORY_SIZE << " bytes (1 MiB)\n";

    std::cout << CLR_CYAN
              << "Stack Pointer (x2): "
              << CLR_YELLOW << "0x"
              << std::hex << MEMORY_SIZE
              << std::dec << CLR_RESET << "\n";

    std::cout << CLR_CYAN
              << "Program Counter initialized to: "
              << CLR_RESET
              << pc << "\n\n";
}
