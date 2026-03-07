#pragma once
#include <cpu/internal/instructions/instruction_params.h>
#include <cstdint>

namespace m68k::InstructionData {

struct ADDX_InstructionData {
    OperandAddressingMode operandAddressingMode;
    OperationSize size;
    uint8_t destinationRegister;
    uint8_t sourceRegister;

}; 


} //namespace m68k::InstructionData