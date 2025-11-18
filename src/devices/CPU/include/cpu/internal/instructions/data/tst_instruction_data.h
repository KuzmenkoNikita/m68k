#pragma once
#include "addressing_mode_instruction_data.h"
#include <variant>

namespace m68k::InstructionData {


struct TSTInstructionData {

    enum class Size : uint8_t {
        BYTE,
        WORD,
        LONG
    };

    Size size;

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