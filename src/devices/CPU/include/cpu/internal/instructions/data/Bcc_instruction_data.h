#pragma once
#include <cpu/internal/instructions/instruction_params.h>
#include <cstdint>
#include <variant>

namespace m68k::InstructionData {

struct BRA_InstructionData {
    Condition condition;
    std::variant<int8_t, int16_t, int32_t>  displacement;
}; 


} //namespace m68k::InstructionData