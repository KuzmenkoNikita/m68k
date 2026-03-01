#pragma once
#include "addressing_mode_instruction_data.h"
#include <cpu/internal/instructions/instruction_params.h>
#include <variant>

namespace m68k::InstructionData {


struct MOVEM_InstructionData {

    enum class Direction : uint8_t {
        REG_TO_MEM,
        MEM_TO_REG
    };

    struct PredecrementModeRegMask {
        bool A7 : 1;
        bool A6 : 1;
        bool A5 : 1;
        bool A4 : 1;
        bool A3 : 1;
        bool A2 : 1;
        bool A1 : 1;
        bool A0 : 1;
        bool D7 : 1;
        bool D6 : 1;
        bool D5 : 1;
        bool D4 : 1;
        bool D3 : 1;
        bool D2 : 1;
        bool D1 : 1;
        bool D0 : 1;
    };

    struct ControlAndPostincrementModeRegMask {
        bool D0 : 1;
        bool D1 : 1;
        bool D2 : 1;
        bool D3 : 1;
        bool D4 : 1;
        bool D5 : 1;
        bool D6 : 1;
        bool D7 : 1;
        bool A0 : 1;
        bool A1 : 1;
        bool A2 : 1;
        bool A3 : 1;
        bool A4 : 1;
        bool A5 : 1;
        bool A6 : 1;
        bool A7 : 1;
    };

    Direction direction;
    OperationSize size;

    std::variant<AddressRegisterModeData,
            AddressModeData,
            AddressWithPostincrementModeData,
            AddressWithPredecrementModeData,
            AddressWithDisplacementModeData,
            AddressWithIndexModeData,
            AbsoluteShortModeData,
            AbsoluteLongModeData>  addressingModeData;

    std::variant<PredecrementModeRegMask, 
                ControlAndPostincrementModeRegMask> registerListMask;
};


} //namespace m68k::InstructionData