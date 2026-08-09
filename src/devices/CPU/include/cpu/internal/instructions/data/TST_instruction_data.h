#pragma once
#include "addressing_mode_instruction_data.h"
#include <cpu/internal/instructions/instruction_params.h>
#include <variant>

namespace m68k::InstructionData {


struct TST_InstructionData {

    using AddressingModeData = std::variant<DataRegisterModeData,
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
                                            ImmediateModeData>;
    AddressingModeData addressingModeData;
    OperationSize size;
};


} //namespace m68k::InstructionData