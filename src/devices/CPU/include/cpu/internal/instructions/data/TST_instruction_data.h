#pragma once
#include "addressing_mode_instruction_data.h"
#include <cpu/internal/instructions/instruction_params.h>
#include <variant>

namespace m68k::InstructionData {


struct TSTInstructionData {

    OperationSize size;

    std::variant<DataRegisterModeData,
                AddressRegisterModeData,
                AddressModeData,
                AddressWithPostincrementModeData,
                AddressWithPredecrementModeData,
                AddressWithDisplacementModeData,
                AddressWithIndexModeData,
                ProgramCounterWithDisplacementModeData,
                ProgramCounterWithIndexModeData,
                AbsoluteShortModeData,
                AbsoluteLongModeData,
                ImmediateModeData>  addressingModeData;

};


} //namespace m68k::InstructionData