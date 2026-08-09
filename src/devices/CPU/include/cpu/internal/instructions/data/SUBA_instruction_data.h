#pragma once
#include "addressing_mode_instruction_data.h"
#include <cpu/internal/instructions/instruction_params.h>
#include <variant>

namespace m68k::InstructionData {


struct SUBA_InstructionData {

    using AddressingModeData = std::variant<DataRegisterModeData,
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
    AddressingModeData addressingModeData;
    OperationSize size;
    uint8_t addressRegisterNumber;
};


} //namespace m68k::InstructionData