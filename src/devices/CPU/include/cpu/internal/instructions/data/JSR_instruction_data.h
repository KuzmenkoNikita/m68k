#pragma once
#include "addressing_mode_instruction_data.h"
#include <variant>

namespace m68k::InstructionData {


struct JSR_InstructionData {

    using AddressingModeData = std::variant<AddressModeData,
                                            AddressWithDisplacementModeData,
                                            AddressWithIndexModeData,
                                            AbsoluteShortModeData,
                                            AbsoluteLongModeData>;
    AddressingModeData addressingModeData;

};


} //namespace m68k::InstructionData