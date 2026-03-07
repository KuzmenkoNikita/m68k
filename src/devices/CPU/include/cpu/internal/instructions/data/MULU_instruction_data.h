#pragma once
#include "addressing_mode_instruction_data.h"
#include <variant>

namespace m68k::InstructionData {


struct MULU_InstructionData {

    uint8_t destinationDataRegister;

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
                ProgramCounterWithIndexModeData>  sourceOperand;
};


} //namespace m68k::InstructionData