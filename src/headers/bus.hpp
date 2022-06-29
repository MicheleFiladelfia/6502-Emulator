#pragma once

#include <cstdint>
#include "ram.hpp"
#include "cpu.hpp"


class Bus{
public:
    Cpu cpu;
    Ram ram;

    Bus();
    void write(uint16_t address, uint8_t data);
    uint8_t read(uint16_t address);
};
