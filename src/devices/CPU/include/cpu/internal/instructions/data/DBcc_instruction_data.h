#pragma once
#include <cpu/internal/instructions/instruction_params.h>
#include <cstdint>

namespace m68k::InstructionData {


struct DBcc_InstructionData {

    Condition condition;
    uint8_t registerNumber;
    int16_t displacement;
};


} //namespace m68k::InstructionData