#pragma once
#include "addressing_mode_instruction_data.h"
#include <cpu/internal/instructions/instruction_params.h>
#include <variant>

namespace m68k::InstructionData {


struct OR_InstructionData {

    enum class Opmode : uint8_t {
        DESTINATION_DN,
        DESTINATION_EA
    };

    OperationSize size;
    Opmode mode;
    uint8_t dataRegisterNumber;

    std::variant<DataRegisterModeData,
            AddressModeData,
            AddressWithPostincrementModeData,
            AddressWithPredecrementModeData,
            AddressWithDisplacementModeData,
            AddressWithIndexModeData,
            AbsoluteShortModeData,
            AbsoluteLongModeData,
            ImmediateModeData,
            ProgramCounterWithDisplacementModeData,
            ProgramCounterWithIndexModeData> addressingModeData;
};


} //namespace m68k::InstructionData