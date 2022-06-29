#pragma once

#include <cstdint>
#include <unordered_map>
#define IS_NEGATIVE(x) ((x) >= 128)
#define TO_8BIT(x) ((x) & 0x00FF)

class Bus;

class Cpu{
public:
    uint8_t accumulator{0x00};
    uint8_t x_index{0x00};
    uint8_t y_index{0x00};
    uint8_t stack_pointer{0xFD};
    uint16_t program_counter{0xFFFC};

    union{
        struct{
            bool carry:1; 
            bool zero:1; 
            bool interrupt:1; 
            bool decimal:1; //On the NES, this flag has no effect...
            bool brk:1; 
            bool unused:1; 
            bool overflow:1; 
            bool negative:1; 
        }flags;

        uint8_t status_register;
    };

    struct{
        uint8_t opcode;
        uint16_t address;
        uint8_t cycles;
    }current_instruction;

    Bus *bus = nullptr;
    void connectBus(Bus *bus){
        this -> bus = bus;
    }
    
    enum addressingMode{IMP,ACC,IMM,ZPG,ZPX,ZPY,REL,ABS,ABX,ABY,IND,IDX,IDY};

    struct instruction{
        void (Cpu::*function)(void);
        addressingMode mode;
        uint8_t cycles;
    };

    std::unordered_map<uint8_t,instruction> table;

    Cpu();

    //Opcodes
    //Load/Store Operations
    void LDA();
    void LDX();
    void LDY();
    void STA();
    void STX();
    void STY();

    //Register Transfer Operations
    void TAX();
    void TAY();
    void TXA();
    void TYA();

    //Stack Operations
    void TSX();
    void TXS();
    void PHA();
    void PHP();
    void PLA();
    void PLP();

    //Logical Operations
    void AND();
    void EOR();
    void ORA();
    void BIT();

    //Arithmetic Operations
    void ADC();
    void SBC();
    void CMP();
    void CPX();
    void CPY();

    //Increments and Decrements
    void INC();
    void INX();
    void INY();
    void DEC();
    void DEX();
    void DEY();

    //Shifts
    void ASL();
    void LSR();
    void ROL();
    void ROR();

    //Jumps and Calls
    void JMP();
    void JSR();
    void RTS();

    //Branches
    void BCC();
    void BCS();
    void BEQ();
    void BMI();
    void BNE();
    void BPL();
    void BVC();
    void BVS();

    //Status Flag Operations
    void CLC();
    void CLD();
    void CLI();
    void CLV();
    void SEC();
    void SED();
    void SEI();

    //System Functions
    void BRK();
    void NOP();
    void RTI();


    void reset();
    void performCycle();
};
