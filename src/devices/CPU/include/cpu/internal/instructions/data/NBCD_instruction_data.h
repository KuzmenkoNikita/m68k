#pragma once
#include "addressing_mode_instruction_data.h"
#include <variant>

namespace m68k::InstructionData {


struct NBCD_InstructionData {

    using AddressingModeData = std::variant<DataRegisterModeData,
                                            AddressModeData,
                                            AddressWithPostincrementModeData,
                                            AddressWithPredecrementModeData,
                                            AddressWithDisplacementModeData,
                                            AddressWithIndexModeData,
                                            AbsoluteShortModeData,
                                            AbsoluteLongModeData>;
    AddressingModeData addressingModeData;

};


} //namespace m68k::InstructionData