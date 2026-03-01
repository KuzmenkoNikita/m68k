#pragma once
#include "addressing_mode_instruction_data.h"
#include <variant>

namespace m68k::InstructionData {


struct LEA_InstructionData {

    uint8_t addrRegNumber;

    std::variant<AddressModeData,
                AddressWithDisplacementModeData,
                AddressWithIndexModeData,
                AbsoluteShortModeData,
                AbsoluteLongModeData,
                ProgramCounterWithDisplacementModeData,
                ProgramCounterWithIndexModeData>  addressingModeData;

};


} //namespace m68k::InstructionData