#pragma once
#include "addressing_mode_instruction_data.h"
#include <cpu/internal/instructions/instruction_params.h>
#include <variant>


namespace m68k::InstructionData {

struct ASL_Memory_InstructionData {

    using AddressingModeData = std::variant<AddressModeData,
                                            AddressWithPostincrementModeData,
                                            AddressWithPredecrementModeData,
                                            AddressWithDisplacementModeData,
                                            AddressWithIndexModeData,
                                            AbsoluteShortModeData,
                                            AbsoluteLongModeData>;
    AddressingModeData operandToBeShifted;
};




} // namespace m68k::InstructionData