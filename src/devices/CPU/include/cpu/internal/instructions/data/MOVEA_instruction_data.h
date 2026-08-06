#pragma once
#include "addressing_mode_instruction_data.h"
#include <cpu/internal/instructions/instruction_params.h>
#include <variant>

namespace m68k::InstructionData {


struct MOVEA_InstructionData {

    using AddressingModeData = std::variant<DataRegisterModeData,
                                            AddressRegisterModeData,
                                            AddressModeData,
                                            AddressWithPostincrementModeData,
                                            AddressWithPredecrementModeData,
                                            AddressWithDisplacementModeData,
                                            AddressWithIndexModeData,
                                            AbsoluteShortModeData,
                                            AbsoluteLongModeData,
                                            ProgramCounterWithDisplacementModeData,
                                            ProgramCounterWithIndexModeData,
                                            ImmediateModeData>;
    AddressingModeData addressingModeData;
    OperationSize size;
    uint8_t addrRegNumber;

};


} //namespace m68k::InstructionData