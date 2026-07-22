#pragma once
#include <cpu/internal/instructions/instruction_params.h>

namespace m68k::InstructionData {

struct ASL_Register_InstructionData {

    enum class ShiftMode : uint8_t{
        IMMEDIATE,
        REGISTER
    };

    uint8_t countOrRegister;
    OperationSize size;
    uint8_t dataRegisterToBeShifted;
    ShiftMode shiftMode;
};


} // namespace m68k::InstructionData