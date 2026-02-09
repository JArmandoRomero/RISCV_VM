#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>

inline int32_t sign_extend(int32_t value, int sign_bit) {
    int shift = 31 - sign_bit;
    return (value << shift) >> shift;
}

#endif
