#pragma once
#include "addressing_mode_instruction_data.h"
#include <cpu/internal/instructions/instruction_params.h>
#include <cstdint>

namespace m68k::InstructionData {


struct CMPA_InstructionData {
    OperationSize size;
    uint8_t addressRegisterNumber;

    std::variant<DataRegisterModeData,
            AddressRegisterModeData,
            AddressModeData,
            AddressWithPostincrementModeData,
            AddressWithPredecrementModeData,
            AddressWithDisplacementModeData,
            AddressWithIndexModeData,
            AbsoluteShortModeData,
            AbsoluteLongModeData,
            ImmediateModeData,
            ProgramCounterWithDisplacementModeData,
            ProgramCounterWithIndexModeData>  addressingModeData;
};


} //namespace m68k::InstructionData