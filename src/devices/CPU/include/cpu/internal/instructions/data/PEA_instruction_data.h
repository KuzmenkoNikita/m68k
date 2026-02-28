#pragma once
#include <cpu/internal/instructions/data/addressing_mode_instruction_data.h>
#include <variant>

namespace m68k::InstructionData {

struct PEA_InstructionData {

    std::variant<AddressModeData,
                AddressWithDisplacementModeData,
                AddressWithIndexModeData,
                AbsoluteShortModeData,
                AbsoluteLongModeData,
                ProgramCounterWithDisplacementModeData,
                ProgramCounterWithIndexModeData>  addressingModeData;

};    

} // namespace m68k::InstructionData