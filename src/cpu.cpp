#include "headers/cpu.hpp"
#include "headers/bus.hpp"
#include <iostream>
Cpu::Cpu(){
    table = {
        {0x00,{&Cpu::BRK,IMP,7}}, {0x01,{&Cpu::ORA,IDX,6}}, {0x05,{&Cpu::ORA,ZPG,3}}, {0x06,{&Cpu::ASL,ZPG,5}}, {0x08,{&Cpu::PHP,IMP,3}}, {0x09,{&Cpu::ORA,IMM,2}}, {0x0A,{&Cpu::ASL,ACC,2}}, {0x0D,{&Cpu::ORA,ABS,4}}, {0x0E,{&Cpu::ASL,ABS,6}},
        {0x10,{&Cpu::BPL,REL,2}}, {0x11,{&Cpu::ORA,IDY,5}}, {0x15,{&Cpu::ORA,ZPX,4}}, {0x16,{&Cpu::ASL,ZPX,6}}, {0x18,{&Cpu::CLC,IMP,2}}, {0x19,{&Cpu::ORA,ABY,4}}, {0x1D,{&Cpu::ORA,ABX,4}}, {0x1E,{&Cpu::ASL,ABX,7}},
        {0x20,{&Cpu::JSR,ABS,6}}, {0x21,{&Cpu::AND,IDX,6}}, {0x24,{&Cpu::BIT,ZPG,3}}, {0x25,{&Cpu::AND,ZPG,3}}, {0x26,{&Cpu::ROL,ZPG,5}}, {0x28,{&Cpu::PLP,IMP,4}}, {0x29,{&Cpu::AND,IMM,2}}, {0x2A,{&Cpu::ROL,ACC,2}}, {0x2C,{&Cpu::BIT,ABS,4}}, {0x2D,{&Cpu::AND,ABS,4}}, {0x2E,{&Cpu::ROL,ABS,6}},
        {0x30,{&Cpu::BMI,REL,2}}, {0x31,{&Cpu::AND,IDY,5}}, {0x35,{&Cpu::AND,ZPX,4}}, {0x36,{&Cpu::ROL,ZPX,6}}, {0x38,{&Cpu::SEC,IMP,2}}, {0x39,{&Cpu::AND,ABY,4}}, {0x3D,{&Cpu::AND,ABX,4}}, {0x3E,{&Cpu::ROL,ABX,7}},
        {0x40,{&Cpu::RTI,IMP,6}}, {0x41,{&Cpu::EOR,IDX,6}}, {0x45,{&Cpu::EOR,ZPG,3}}, {0x46,{&Cpu::LSR,ZPG,5}}, {0x48,{&Cpu::PHA,IMP,3}}, {0x49,{&Cpu::EOR,IMM,2}}, {0x4A,{&Cpu::LSR,ACC,2}}, {0x4C,{&Cpu::JMP,ABS,3}}, {0x4D,{&Cpu::EOR,ABS,4}}, {0x4E,{&Cpu::LSR,ABS,6}},
        {0x50,{&Cpu::BVC,REL,2}}, {0x51,{&Cpu::EOR,IDY,5}}, {0x55,{&Cpu::EOR,ZPX,4}}, {0x56,{&Cpu::LSR,ZPX,6}}, {0x58,{&Cpu::CLI,IMP,2}}, {0x59,{&Cpu::EOR,ABY,4}}, {0x5D,{&Cpu::EOR,ABX,4}}, {0x5E,{&Cpu::LSR,ABX,7}},
        {0x60,{&Cpu::RTS,IMP,6}}, {0x61,{&Cpu::ADC,IDX,6}}, {0x65,{&Cpu::ADC,ZPG,3}}, {0x66,{&Cpu::ROR,ZPG,5}}, {0x68,{&Cpu::PLA,IMP,4}}, {0x69,{&Cpu::ADC,IMM,2}}, {0x6A,{&Cpu::ROR,ACC,2}}, {0x6C,{&Cpu::JMP,IND,5}}, {0x6D,{&Cpu::ADC,ABS,4}}, {0x6E,{&Cpu::ROR,ABS,6}},
        {0x70,{&Cpu::BVS,REL,2}}, {0x71,{&Cpu::ADC,IDY,5}}, {0x75,{&Cpu::ADC,ZPX,4}}, {0x76,{&Cpu::ROR,ZPX,6}}, {0x78,{&Cpu::SEI,IMP,2}}, {0x79,{&Cpu::ADC,ABY,4}}, {0x7D,{&Cpu::ADC,ABX,4}}, {0x7E,{&Cpu::ROR,ABX,7}},
        {0x81,{&Cpu::STA,IDX,6}}, {0x84,{&Cpu::STY,ZPG,3}}, {0x85,{&Cpu::STA,ZPG,3}}, {0x86,{&Cpu::STX,ZPG,3}}, {0x88,{&Cpu::DEY,IMP,2}}, {0x8A,{&Cpu::TXA,IMP,2}}, {0x8C,{&Cpu::STY,ABS,4}}, {0x8D,{&Cpu::STA,ABS,4}}, {0x8E,{&Cpu::STX,ABS,4}},     
        {0x90,{&Cpu::BCC,REL,2}}, {0x91,{&Cpu::STA,IDY,6}}, {0x94,{&Cpu::STY,ZPX,4}}, {0x95,{&Cpu::STA,ZPX,4}}, {0x96,{&Cpu::STX,ZPY,4}}, {0x98,{&Cpu::TYA,IMP,2}}, {0x99,{&Cpu::STA,ABY,5}}, {0x9A,{&Cpu::TXS,IMP,2}}, {0x9D,{&Cpu::STA,ABX,5}}, 
        {0xA0,{&Cpu::LDY,IMM,2}}, {0xA1,{&Cpu::LDA,IDX,6}}, {0xA2,{&Cpu::LDX,IMM,2}}, {0xA4,{&Cpu::LDY,ZPG,3}}, {0xA5,{&Cpu::LDA,ZPG,3}}, {0xA6,{&Cpu::LDX,ZPG,3}}, {0xA8,{&Cpu::TAY,IMP,2}}, {0xA9,{&Cpu::LDA,IMM,2}}, {0xAA,{&Cpu::TAX,IMP,2}}, {0xAC,{&Cpu::LDY,ABS,4}}, {0xAD,{&Cpu::LDA,ABS,4}}, {0xAE,{&Cpu::LDX,ABS,4}},     
        {0xB0,{&Cpu::BCS,REL,2}}, {0xB1,{&Cpu::LDA,IDY,5}}, {0xB4,{&Cpu::LDY,ZPX,4}}, {0xB5,{&Cpu::LDA,ZPX,4}}, {0xB6,{&Cpu::LDX,ZPY,4}}, {0xB8,{&Cpu::CLV,IMP,2}}, {0xB9,{&Cpu::LDA,ABY,4}}, {0xBA,{&Cpu::TSX,IMP,2}}, {0xBC,{&Cpu::LDY,ABX,4}}, {0xBD,{&Cpu::LDA,ABX,4}}, {0xBE,{&Cpu::LDX,ABY,4}},
        {0xC0,{&Cpu::CPY,IMM,2}}, {0xC1,{&Cpu::CMP,IDX,6}}, {0xC4,{&Cpu::CPY,ZPG,3}}, {0xC5,{&Cpu::CMP,ZPG,3}}, {0xC6,{&Cpu::DEC,ZPG,5}}, {0xC8,{&Cpu::INY,IMP,2}}, {0xC9,{&Cpu::CMP,IMM,2}}, {0xCA,{&Cpu::DEX,IMP,2}}, {0xCC,{&Cpu::CPY,ABS,4}}, {0xCD,{&Cpu::CMP,ABS,4}}, {0xCE,{&Cpu::DEC,ABS,6}},     
        {0xD0,{&Cpu::BNE,REL,2}}, {0xD1,{&Cpu::CMP,IDY,5}}, {0xD5,{&Cpu::CMP,ZPX,4}}, {0xD6,{&Cpu::DEC,ZPX,6}}, {0xD8,{&Cpu::CLD,IMP,2}}, {0xD9,{&Cpu::CMP,ABY,4}}, {0xDD,{&Cpu::CMP,ABX,4}}, {0xDE,{&Cpu::DEC,ABX,7}},
        {0xE0,{&Cpu::CPX,IMM,2}}, {0xE1,{&Cpu::SBC,IDX,6}}, {0xE4,{&Cpu::CPX,ZPG,3}}, {0xE5,{&Cpu::SBC,ZPG,3}}, {0xE6,{&Cpu::INC,ZPG,5}}, {0xE8,{&Cpu::INX,IMP,2}}, {0xE9,{&Cpu::SBC,IMM,2}}, {0xEA,{&Cpu::NOP,IMP,2}}, {0xEC,{&Cpu::CPX,ABS,4}}, {0xED,{&Cpu::SBC,ABS,4}}, {0xEE,{&Cpu::INC,ABS,6}},     
        {0xF0,{&Cpu::BEQ,REL,2}}, {0xF1,{&Cpu::SBC,IDY,5}}, {0xF5,{&Cpu::SBC,ZPX,4}}, {0xF6,{&Cpu::INC,ZPX,6}}, {0xF8,{&Cpu::SED,IMP,2}}, {0xF9,{&Cpu::SBC,ABY,4}}, {0xFD,{&Cpu::SBC,ABX,4}}, {0xFE,{&Cpu::INC,ABX,7}}
    };
}

void Cpu::performCycle(){
    current_instruction.cycles = 0;
    if(current_instruction.cycles != 0){
        current_instruction.cycles--;
        return;
    }

    uint16_t first_byte, second_byte, arg, temp;

    current_instruction.opcode = bus -> read(program_counter++);
    current_instruction.cycles += table[current_instruction.opcode].cycles;

    printf("%x ",current_instruction.opcode);

    switch(table[current_instruction.opcode].mode){
        case IMP:
        break;
        case ACC:
        break;
        case IMM:
            current_instruction.address = program_counter++;
        break;
        case ZPG:
            current_instruction.address = bus -> read(program_counter++);
            current_instruction.address = TO_8BIT(current_instruction.address);
            break;
        case ZPX:
            current_instruction.address = bus -> read(program_counter++) + x_index;
            current_instruction.address = TO_8BIT(current_instruction.address);
        break;
        case ZPY:
            current_instruction.address = bus -> read(program_counter++) + y_index;
            current_instruction.address = TO_8BIT(current_instruction.address);
        break;
        case REL:
            current_instruction.address = bus -> read(program_counter++);
        break;
        case ABS:
            first_byte = bus -> read(program_counter++);
            second_byte = bus -> read(program_counter++);
            current_instruction.address = (second_byte << 8) | first_byte;
        break;
        case ABX:
            first_byte = bus -> read(program_counter++);
            second_byte = bus -> read(program_counter++);
            current_instruction.address = (second_byte << 8) | first_byte;

            if((current_instruction.address & 0xFF00) != ((current_instruction.address + x_index) & 0xFF00))
                current_instruction.cycles++;
                
            current_instruction.address += x_index;
        break;
        case ABY:
            first_byte = bus -> read(program_counter++);
            second_byte = bus -> read(program_counter++);
            current_instruction.address = (second_byte << 8) | first_byte;
                
            if((current_instruction.address & 0xFF00) != ((current_instruction.address + y_index) & 0xFF00))
                current_instruction.cycles++;
                
            current_instruction.address += y_index;
        break;
        case IND:
            first_byte = bus -> read(program_counter++);
            second_byte = bus -> read(program_counter++);
            temp = (second_byte << 8) | first_byte;

            if(first_byte == 0x00FF){
                //Simulating HW bug
                current_instruction.address = (bus -> read(temp & 0xFF00) << 8) | bus -> read(temp);
            }else{
                current_instruction.address = (bus -> read(temp + 1) << 8) | bus -> read(temp);
            }
        break;
        case IDX:
            arg = bus -> read(program_counter) + static_cast<uint16_t>(x_index);
            program_counter++;
            first_byte = bus -> read(TO_8BIT(arg));
            second_byte = bus -> read(TO_8BIT(arg + 1));
            current_instruction.address = (second_byte << 8) | first_byte;
        break;
        case IDY:
            arg = bus -> read(program_counter);
            program_counter++;

            first_byte = bus -> read(TO_8BIT(arg));
            second_byte = bus -> read(TO_8BIT(arg + 1));

            if((current_instruction.address & 0xFF00) != ((current_instruction.address + y_index) & 0xFF00))
                current_instruction.cycles++;

            current_instruction.address = ((second_byte << 8) | first_byte) + y_index;
        break;
    }

    (this->*table[current_instruction.opcode].function)();
}

void Cpu::reset(){
    program_counter = 0xFFFC;
    stack_pointer = 0xFD;
    status_register = 0x00;
    accumulator = 0x00;
    x_index = 0x00;
    y_index = 0x00;
}

void Cpu::LDA(){
    accumulator = bus -> read(current_instruction.address);
    flags.zero = (accumulator == 0);
    flags.negative = IS_NEGATIVE(accumulator);
}

void Cpu::LDX(){
    x_index = bus -> read(current_instruction.address);
    flags.zero = (x_index == 0);
    flags.negative = IS_NEGATIVE(x_index);
}

void Cpu::LDY(){
    y_index = bus -> read(current_instruction.address);
    flags.zero = (y_index == 0);
    flags.negative = IS_NEGATIVE(y_index);
}

void Cpu::STA(){
    bus -> write(current_instruction.address,accumulator);
}

void Cpu::STX(){
    bus -> write(current_instruction.address,x_index);
}

void Cpu::STY(){
    bus -> write(current_instruction.address,y_index);
}

void Cpu::TAX(){
    x_index = accumulator;
    flags.zero = (x_index == 0);
    flags.negative = IS_NEGATIVE(x_index);
}

void Cpu::TAY(){
    y_index = accumulator;
    flags.zero = (y_index == 0);
    flags.negative = IS_NEGATIVE(y_index);
}

void Cpu::TXA(){
    accumulator = x_index;
    flags.zero = (accumulator == 0);
    flags.negative = IS_NEGATIVE(accumulator);
}

void Cpu::TYA(){
    accumulator = y_index;
    flags.zero = (accumulator == 0);
    flags.negative = IS_NEGATIVE(accumulator);
}

void Cpu::TSX(){
    x_index = stack_pointer;
    flags.zero = (x_index == 0);
    flags.negative = IS_NEGATIVE(x_index);
}

void Cpu::TXS(){
    stack_pointer = x_index;
    flags.zero = (stack_pointer == 0);
    flags.negative = IS_NEGATIVE(stack_pointer);
}

void Cpu::PHA(){
    bus -> write(0x0100 + stack_pointer, accumulator);
    stack_pointer--;
}

void Cpu::PHP(){
    flags.brk = true;
    flags.unused = true;
    bus -> write(0x0100 + stack_pointer, status_register);
    flags.brk = false;
    flags.unused = false;
    stack_pointer--;
}

void Cpu::PLA(){
    stack_pointer++;
    accumulator = bus -> read(0x0100 + stack_pointer);
    flags.zero = (accumulator == 0);
    flags.negative = IS_NEGATIVE(accumulator);
}

void Cpu::PLP(){
    stack_pointer++;
    status_register = bus -> read(0x0100 + stack_pointer);
}

void Cpu::AND(){
    accumulator &= bus -> read(current_instruction.address);
    flags.zero = (accumulator == 0);
    flags.negative = IS_NEGATIVE(accumulator);
}

void Cpu::EOR(){
    accumulator ^= bus -> read(current_instruction.address);
    flags.zero = (accumulator == 0);
    flags.negative = IS_NEGATIVE(accumulator);
}

void Cpu::ORA(){
    accumulator |= bus -> read(current_instruction.address);
    flags.zero = (accumulator == 0);
    flags.negative = IS_NEGATIVE(accumulator);
}

void Cpu::BIT(){
    uint8_t M = bus -> read(current_instruction.address);
    flags.zero = (accumulator & M) == 0;
    flags.negative = M & (1 >> 7);
    flags.overflow = M & (1 >> 6);
}

void Cpu::ADC(){
    uint8_t M = bus -> read(current_instruction.address);
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(M) + static_cast<uint16_t>(flags.carry);
    flags.carry = result > 255;
    flags.overflow = IS_NEGATIVE(~((uint16_t)accumulator ^ (uint16_t)M) & ((uint16_t)accumulator ^ (uint16_t)result));
    flags.negative = (result & 0x80);

    //trasforming the result in 8 bit
    result &= 0x00FF;

    flags.zero = (result == 0);
    accumulator = result;
}

void Cpu::SBC(){
    uint8_t M = bus -> read(current_instruction.address) ^ 0x00FF;
    uint16_t result = static_cast<uint16_t>(accumulator) + static_cast<uint16_t>(M) + static_cast<uint16_t>(flags.carry);
    flags.carry = result > 255;
    flags.overflow = IS_NEGATIVE(((uint16_t)result ^ (uint16_t)accumulator) & ((uint16_t)result ^ (uint16_t)M));
    flags.negative = (result & 0x80);

    //trasforming the result in 8 bit
    result &= 0x00FF;

    flags.zero = (result == 0);
    accumulator = result;
}

void Cpu::CMP(){
    uint8_t M = bus -> read(current_instruction.address);
    uint16_t result = static_cast<uint8_t>(accumulator) - static_cast<uint8_t>(M);
    flags.carry = (accumulator >= M);
    flags.overflow = ((result & 0x00FF) == 0);
    flags.negative = IS_NEGATIVE(result);
}

void Cpu::CPX(){
    uint8_t M = bus -> read(current_instruction.address);
    uint16_t result = static_cast<uint8_t>(x_index) - static_cast<uint8_t>(M);
    flags.carry = (x_index >= M);
    flags.overflow = ((result & 0x00FF) == 0);
    flags.negative = IS_NEGATIVE(result);
}

void Cpu::CPY(){
    uint8_t M = bus -> read(current_instruction.address);
    uint16_t result = static_cast<uint8_t>(y_index) - static_cast<uint8_t>(M);
    flags.carry = (y_index >= M);
    flags.overflow = ((result & 0x00FF) == 0);
    flags.negative = IS_NEGATIVE(result);
}

void Cpu::INC(){
    uint8_t M = bus -> read(current_instruction.address) + 1;
    bus -> write(current_instruction.address, M);
    flags.negative = IS_NEGATIVE(M);
    flags.zero = (M == 0);
}

void Cpu::INX(){
    x_index++;
    flags.negative = IS_NEGATIVE(x_index);
    flags.zero = (x_index == 0);
}

void Cpu::INY(){
    y_index++;
    flags.negative = IS_NEGATIVE(y_index);
    flags.zero = (y_index == 0);
}

void Cpu::DEC(){
    uint8_t M = (bus -> read(current_instruction.address)) - 1;
    bus -> write(current_instruction.address, M);
    flags.negative = IS_NEGATIVE(M);
    flags.zero = (M == 0);
}

void Cpu::DEX(){
    x_index--;
    flags.negative = IS_NEGATIVE(x_index);
    flags.zero = (x_index == 0);
}

void Cpu::DEY(){
    y_index--;
    flags.negative = IS_NEGATIVE(y_index);
    flags.zero = (y_index == 0);
}

void Cpu::ASL(){
    uint16_t operand = accumulator;
    if(table[current_instruction.opcode].mode != ACC)
        operand = (bus -> read(current_instruction.address));

    operand = operand << 1;

    flags.carry = (operand & (0xFF00)) != 0;
    flags.negative = IS_NEGATIVE(operand);
    flags.zero = (TO_8BIT(operand) == 0);


    if(table[current_instruction.opcode].mode == ACC){
        accumulator = operand;
    }else{
        bus -> write(current_instruction.address,TO_8BIT(operand));
    }
}

void Cpu::LSR(){
    uint16_t operand = accumulator;
    if(table[current_instruction.opcode].mode != ACC)
        operand = (bus -> read(current_instruction.address));

    operand = operand >> 1;

    flags.carry = (operand & (0xFF00)) != 0;
    flags.negative = IS_NEGATIVE(operand);
    flags.zero = (TO_8BIT(operand) == 0);


    if(table[current_instruction.opcode].mode == ACC){
        accumulator = operand;
    }else{
        bus -> write(current_instruction.address,TO_8BIT(operand));
    }
}

void Cpu::ROL(){
    uint16_t operand = accumulator;
    if(table[current_instruction.opcode].mode != ACC)
        operand = (bus -> read(current_instruction.address));

    operand = operand << 1;

    //adding carry to bit 0
    operand = operand | flags.carry;

    flags.carry = (operand & (0xFF00)) != 0;
    flags.negative = IS_NEGATIVE(operand);
    flags.zero = (TO_8BIT(operand) == 0);


    if(table[current_instruction.opcode].mode == ACC){
        accumulator = TO_8BIT(operand);
    }else{
        bus -> write(current_instruction.address,TO_8BIT(operand));
    }
}

void Cpu::ROR(){
    uint16_t operand = accumulator;
    if(table[current_instruction.opcode].mode != ACC)
        operand = (bus -> read(current_instruction.address));

    uint16_t temp = (flags.carry << 7) | (operand >> 1);
 
    flags.carry = (temp & (0xFF00)) != 0;
    flags.negative = IS_NEGATIVE(temp);
    flags.zero = (TO_8BIT(temp) == 0);


    if(table[current_instruction.opcode].mode == ACC){
        accumulator = TO_8BIT(temp);
    }else{
        bus -> write(current_instruction.address,TO_8BIT(temp));
    }
}

void Cpu::JMP(){
    program_counter = current_instruction.address;
}

void Cpu::JSR(){
    program_counter--;

    bus -> write(0x0100 + stack_pointer, TO_8BIT(program_counter >> 8));
    stack_pointer--;
    bus -> write(0x0100 + stack_pointer, TO_8BIT(program_counter));
    stack_pointer--;

    program_counter = current_instruction.address;
}

void Cpu::RTS(){
    stack_pointer++;
    uint16_t first_byte = static_cast<uint16_t>(bus -> read(0x0100 + stack_pointer));
    stack_pointer++;
    uint16_t second_byte = static_cast<uint16_t>(bus -> read(0x0100 + stack_pointer));

    program_counter = (second_byte << 8) | first_byte;
    program_counter++;
}

void Cpu::BCC(){
    if(!flags.carry){
        current_instruction.cycles++;

        if((program_counter & 0xFF00) != ((program_counter + current_instruction.address) & 0xFF00))
            current_instruction.cycles++;
        
        program_counter += current_instruction.address;
    }
}

void Cpu::BCS(){
    if(flags.carry){
        current_instruction.cycles++;

        if((program_counter & 0xFF00) != ((program_counter + current_instruction.address) & 0xFF00))
            current_instruction.cycles++;
        
        program_counter += current_instruction.address;
    }
}

void Cpu::BEQ(){
    if(flags.zero){
        current_instruction.cycles++;

        if((program_counter & 0xFF00) != ((program_counter + current_instruction.address) & 0xFF00))
            current_instruction.cycles++;
        
        program_counter += current_instruction.address;
    }
}

void Cpu::BMI(){
    if(flags.negative){
        current_instruction.cycles++;

        if((program_counter & 0xFF00) != ((program_counter + current_instruction.address) & 0xFF00))
            current_instruction.cycles++;
        
        program_counter += current_instruction.address;
    }
}

void Cpu::BNE(){
    if(!flags.carry){
        current_instruction.cycles++;

        if((program_counter & 0xFF00) != ((program_counter + current_instruction.address) & 0xFF00))
            current_instruction.cycles++;
        
        program_counter += current_instruction.address;
    }
}

void Cpu::BPL(){
    if(!flags.negative){
        current_instruction.cycles++;

        if((program_counter & 0xFF00) != ((program_counter + current_instruction.address) & 0xFF00))
            current_instruction.cycles++;
        
        program_counter += current_instruction.address;
    }
}

void Cpu::BVC(){
    if(!flags.overflow){
        current_instruction.cycles++;

        if((program_counter & 0xFF00) != ((program_counter + current_instruction.address) & 0xFF00))
            current_instruction.cycles++;
        
        program_counter += current_instruction.address;
    }
}

void Cpu::BVS(){
    if(flags.overflow){
        current_instruction.cycles++;

        if((program_counter & 0xFF00) != ((program_counter + current_instruction.address) & 0xFF00))
            current_instruction.cycles++;
        
        program_counter += current_instruction.address;
    }
}

void Cpu::CLC(){
    flags.carry = false;
}

void Cpu::CLD(){
    flags.decimal = false;
}

void Cpu::CLI(){
    flags.interrupt = false;
}

void Cpu::CLV(){
    flags.overflow = false;
}

void Cpu::SEC(){
    flags.carry = true;
}

void Cpu::SED(){
    flags.decimal = true;
}

void Cpu::SEI(){
    flags.interrupt = true;
}

void Cpu::BRK(){
    program_counter++;

    flags.interrupt = true;

    bus -> write(0x0100 + stack_pointer, TO_8BIT(program_counter >> 8));
    stack_pointer--;
    bus -> write(0x0100 + stack_pointer, TO_8BIT(program_counter));
    stack_pointer--;

    flags.brk = true;
    bus -> write(0x0100 + stack_pointer, status_register);
    stack_pointer--;
    flags.brk = false;

    program_counter = static_cast<uint16_t>(bus -> read(0xFFFE)) | static_cast<uint16_t>(bus -> read(0xFFFF)) << 8;
}

void Cpu::NOP(){
    return;
}

void Cpu::RTI(){
    stack_pointer++;
    status_register = (bus -> read(0x0100 + stack_pointer)) & 0b11110011;
    
    stack_pointer++;
    uint16_t first_byte = bus -> read(0x0100 + stack_pointer);
    stack_pointer++;
    uint16_t second_byte = bus -> read(0x0100 + stack_pointer);

    program_counter = (second_byte << 8) | first_byte;
}
