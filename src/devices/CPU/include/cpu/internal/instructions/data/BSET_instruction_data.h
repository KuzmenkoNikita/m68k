#pragma once
#include "addressing_mode_instruction_data.h"
#include <cpu/internal/instructions/instruction_params.h>
#include <variant>

namespace m68k::InstructionData {

struct BSET_InstructionData {

    enum class Type : uint8_t {
        DataRegister,
        Immediate
    };

    struct ImmediateData {
        uint8_t bitNumber;
    };

    struct DataRegisterData {
        uint8_t dataRegNumber;
    };

    Type type;

    std::variant<ImmediateData, DataRegisterData> TypeData;

    std::variant<DataRegisterModeData,
                AddressModeData,
                AddressWithPostincrementModeData,
                AddressWithPredecrementModeData,
                AddressWithDisplacementModeData,
                AddressWithIndexModeData,
                AbsoluteShortModeData,
                AbsoluteLongModeData>  addressingModeData;
}; 


} //namespace m68k::InstructionData