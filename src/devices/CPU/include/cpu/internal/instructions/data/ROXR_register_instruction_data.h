#pragma once
#include <cpu/internal/instructions/instruction_params.h>

namespace m68k::InstructionData {

struct ROXR_Register_InstructionData {

    enum class RotateMode : uint8_t{
        IMMEDIATE,
        REGISTER
    };

    uint8_t countOrRegister;
    OperationSize size;
    uint8_t dataRegisterToBeRotated;
    RotateMode shiftMode;

}; 


} //namespace m68k::InstructionData