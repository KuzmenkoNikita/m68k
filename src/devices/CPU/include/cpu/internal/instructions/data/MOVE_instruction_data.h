#pragma once
#include "addressing_mode_instruction_data.h"
#include <cpu/internal/instructions/instruction_params.h>
#include <variant>

namespace m68k::InstructionData {


struct MOVE_InstructionData {

    using DstAddressingModeData = std::variant<DataRegisterModeData,
                                                AddressModeData,
                                                AddressWithPostincrementModeData,
                                                AddressWithPredecrementModeData,
                                                AddressWithDisplacementModeData,
                                                AddressWithIndexModeData,
                                                AbsoluteShortModeData,
                                                AbsoluteLongModeData>;

    using SrcAddressingModeData = std::variant<DataRegisterModeData,
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
                                                ProgramCounterWithIndexModeData>;

    OperationSize size;
    SrcAddressingModeData sourceAddressingModeData;
    DstAddressingModeData destinationAddressingModeData;

};


} //namespace m68k::InstructionData