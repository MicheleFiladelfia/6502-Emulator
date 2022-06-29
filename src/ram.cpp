#include "headers/ram.hpp"

Ram::Ram(){
    erase();
}

void Ram::erase(){
    std::fill(begin(), end(), 0x00);
}