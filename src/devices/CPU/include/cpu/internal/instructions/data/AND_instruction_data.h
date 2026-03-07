#pragma once
#include "addressing_mode_instruction_data.h"
#include <cpu/internal/instructions/instruction_params.h>
#include <variant>

namespace m68k::InstructionData {


struct AND_InstructionData {

    DestinationOperandType destOperandType;
    OperationSize size;
    uint8_t dataRegisterNumber;

    std::variant<DataRegisterModeData,
            AddressModeData,
            AddressWithPostincrementModeData,
            AddressWithPredecrementModeData,
            AddressWithDisplacementModeData,
            AddressWithIndexModeData,
            AbsoluteShortModeData,
            AbsoluteLongModeData,
            ImmediateModeData,
            ProgramCounterWithDisplacementModeData,
            ProgramCounterWithIndexModeData> addressingModeData;
};


} //namespace m68k::InstructionData