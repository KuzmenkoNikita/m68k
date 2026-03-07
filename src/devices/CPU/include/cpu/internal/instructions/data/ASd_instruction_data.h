#pragma once
#include "addressing_mode_instruction_data.h"
#include <cpu/internal/instructions/instruction_params.h>
#include <variant>

namespace m68k::InstructionData {

struct ASd_InstructionData {

    struct RegisterShiftData {

        enum class ShiftMode : uint8_t{
            IMMEDIATE,
            REGISTER
        };

        uint8_t countOrRegister;
        OperationSize size;
        uint8_t dataRegisterToBeShifted;
        ShiftMode shiftMode;
    };

    struct MemoryShiftData {

        std::variant<AddressModeData,
                    AddressWithPostincrementModeData,
                    AddressWithPredecrementModeData,
                    AddressWithDisplacementModeData,
                    AddressWithIndexModeData,
                    AbsoluteShortModeData,
                    AbsoluteLongModeData>  operandToBeShifted;
    };

    Direction direction;
    std::variant<RegisterShiftData, MemoryShiftData> shiftData;
}; 


} //namespace m68k::InstructionData