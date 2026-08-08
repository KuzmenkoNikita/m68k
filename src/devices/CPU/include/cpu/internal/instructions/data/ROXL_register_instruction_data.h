#pragma once
#include <cpu/internal/instructions/instruction_params.h>

namespace m68k::InstructionData {

struct ROXL_Register_InstructionData {

    enum class RotateMode : uint8_t{
        IMMEDIATE,
        REGISTER
    };

    uint8_t countOrRegister;
    OperationSize size;
    uint8_t dataRegisterToBeRotated;
    RotateMode rotateMode;

}; 


} //namespace m68k::InstructionData