#pragma once
#include "addressing_mode_instruction_data.h"
#include <variant>

namespace m68k::InstructionData {


struct MOVE_from_SR_InstructionData {

    std::variant<DataRegisterModeData,
                AddressModeData,
                AddressWithPostincrementModeData,
                AddressWithPredecrementModeData,
                AddressWithDisplacementModeData,
                AddressWithIndexModeData,
                AbsoluteShortModeData,
                AbsoluteLongModeData>  adressingModeData;
};


} //namespace m68k::InstructionData