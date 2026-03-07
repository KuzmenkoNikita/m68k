#pragma once
#include <cpu/internal/instructions/instruction_params.h>
#include <cstdint>

namespace m68k::InstructionData {

struct SUBX_InstructionData {
    OperandAddressingMode operandAddressingMode;
    uint8_t destinationRegister;
    uint8_t sourceRegister;

}; 


} //namespace m68k::InstructionData