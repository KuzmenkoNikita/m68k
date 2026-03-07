#pragma once
#include <cpu/internal/instructions/instruction_params.h>
#include <cstdint>

namespace m68k::InstructionData {


struct CMPM_InstructionData {
    OperationSize size;
    uint8_t destinationRegisterNumber;
    uint8_t sourceRegisterNumber;
};


} //namespace m68k::InstructionData