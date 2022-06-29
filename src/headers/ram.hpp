#pragma once

#include <array>
#include <cstdint>

class Ram: public std::array<uint8_t, 0x10000>{
public:
    Ram();
    void erase();
};