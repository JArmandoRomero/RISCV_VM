#ifndef ELF_LOADER_HPP
#define ELF_LOADER_HPP

#include <string>
#include "machine.hpp"

bool load_elf(const std::string& filename, Machine& machine);

#endif
