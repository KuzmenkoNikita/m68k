#pragma once
#include <cstdint>

namespace m68k {

enum class OperandType : uint8_t {
    NONE,
    DATA_REGISTER,
    ADDRESS_REGISTER,
    ADDRESS,
    ADDRESS_WITH_POSTINCREMENT,
    ADDRESS_WITH_PREDECREMENT,
    ADDRESS_WITH_DISPLACEMENT,
    ADDRESS_WITH_INDEX,
    PC_WITH_DISPLACEMENT,
    PC_WITH_INDEX,
    ABSOLUTE_SHORT,
    ABSOLUTE_LONG,
    IMMEDIATE
};

enum class OperandSize : uint8_t {
    BYTE,
    WORD,
    LONG
};

struct Operand {
    OperandType type = OperandType::NONE;
    OperandSize size = OperandSize::WORD;
    
    struct {
        uint8_t reg = 0;        
        int16_t displacement = 0; 
        uint8_t indexReg = 0;   
        bool isAddressReg = false; 
        bool indexSizeLong = false; 
    } details;
};

enum class InstructionType : uint8_t {
    ORI_to_CCR,
    ORI_to_SR,
    ORI,
    ANDI_to_CCR,
    ANDI_to_SR,
    ANDI,
    SUBI,
    ADDI,
    EORI_to_CCR,
    EORI_to_SR,
    EORI,
    CMPI,
    BTST,
    BCHG,
    BCLR,
    BSET,
    MOVEP,
    MOVEA,
    MOVE,
    MOVE_from_SR,
    MOVE_to_CCR,
    MOVE_to_SR,
    NEGX,
    CLR,
    NEG,
    NOT,
    EXT,
    NBCD,
    SWAP,
    PEA,
    ILLEGAL,
    TAS,
    TST,
    TRAP,
    LINK,
    UNLK,
    MOVE_USP,
    RESET,
    NOP,
    STOP,
    RTE,
    RTS,
    TRAPV,
    RTR,
    JSR,
    JMP,
    MOVEM,
    LEA,
    CHK,
    ADDQ,
    SUBQ,
    Scc,
    DBcc,
    BRA,
    BSR,
    Bcc,
    MOVEQ,
    DIVU,
    DIVS,
    SBCD,
    OR,
    SUB,
    SUBX,
    SUBA,
    EOR,
    CMPM,
    CMP,
    CMPA,
    MULU,
    MULS,
    ABCD,
    EXG,
    AND,
    ADD,
    ADDX,
    ADDA,
    ASL,
    ASR,
    LSL,
    LSR,
    ROXL,
    ROXR,
    ROL,
    ROR,
    INVALID
};


struct Instruction {
    InstructionType type = InstructionType::INVALID;
    OperandSize size = OperandSize::WORD;
    Operand src;
    Operand dst;
    uint32_t length = 2;       
};

} // namespace m68k