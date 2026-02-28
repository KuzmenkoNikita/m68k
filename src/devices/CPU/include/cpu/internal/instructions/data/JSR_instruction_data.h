#pragma once
#include "addressing_mode_instruction_data.h"
#include <variant>

namespace m68k::InstructionData {


struct JSR_InstructionData {

    std::variant<AddressModeData,
                AddressWithDisplacementModeData,
                AddressWithIndexModeData,
                AbsoluteShortModeData,
                AbsoluteLongModeData>  addressingModeData;

};


} //namespace m68k::InstructionData