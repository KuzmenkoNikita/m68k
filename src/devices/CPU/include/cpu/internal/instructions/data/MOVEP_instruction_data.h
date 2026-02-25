#pragma once
#include <cstdint>


namespace m68k::InstructionData {

struct MOVEP_InstructionData {

    enum class OpMode : uint8_t{
        WORD_MEM_TO_REG,
        LONG_MEM_TO_REG,
        WORD_REG_TO_MEM,
        LONG_REG_TO_MEM
    };

    int16_t displacement; 
    uint8_t dataRegNumber;
    uint8_t addrRegNumber;
    OpMode mode;
}; 


} //namespace m68k::InstructionData