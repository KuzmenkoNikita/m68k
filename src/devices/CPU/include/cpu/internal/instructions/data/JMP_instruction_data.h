#pragma once
#include "addressing_mode_instruction_data.h"
#include <variant>

namespace m68k::InstructionData {


struct JMP_InstructionData {

    std::variant<AddressModeData,
                AddressWithDisplacementModeData,
                AddressWithIndexModeData,
                AbsoluteShortModeData,
                AbsoluteLongModeData,
                ProgramCounterWithDisplacementModeData,
                ProgramCounterWithIndexModeData>  addressingModeData;

};


} //namespace m68k::InstructionData