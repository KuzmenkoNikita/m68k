#pragma once
#include "addressing_mode_instruction_data.h"
#include <cpu/internal/instructions/instruction_params.h>
#include <variant>

namespace m68k::InstructionData {

struct BSET_Register_InstructionData {

    uint8_t dataRegNumber;

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