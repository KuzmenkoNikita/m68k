#pragma once
#include "addressing_mode_instruction_data.h"
#include <cpu/internal/instructions/instruction_params.h>
#include <variant>

namespace m68k::InstructionData {


struct ADDA_InstructionData {

    OperationSize size;

    uint8_t destinationAddressRegister;

    std::variant<DataRegisterModeData,
                AddressRegisterModeData,
                AddressModeData,
                AddressWithPostincrementModeData,
                AddressWithPredecrementModeData,
                AddressWithDisplacementModeData,
                AddressWithIndexModeData,
                AbsoluteShortModeData,
                AbsoluteLongModeData,
                ImmediateModeData,
                ProgramCounterWithDisplacementModeData,
                ProgramCounterWithIndexModeData>  sourceOperand;

};


} //namespace m68k::InstructionData