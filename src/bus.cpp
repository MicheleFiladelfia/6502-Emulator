#include "headers/bus.hpp"

void Bus::write(uint16_t address, uint8_t data){
    if(address >= 0x0000 && address <= 0xFFFF)
        ram.at(address) = data;
}

uint8_t Bus::read(uint16_t address){
    if(address >= 0x0000 && address <= 0xFFFF)
        return ram.at(address);

    return 0x0000;
}

Bus::Bus(){
    cpu.connectBus(this);
}
