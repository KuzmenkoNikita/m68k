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

    using AddressingModeData = std::variant<AddressRegisterModeData,
                                            AddressModeData,
                                            AddressWithPostincrementModeData,
                                            AddressWithPredecrementModeData,
                                            AddressWithDisplacementModeData,
                                            AddressWithIndexModeData,
                                            AbsoluteShortModeData,
                                            AbsoluteLongModeData>;
                                            
    AddressingModeData addressingModeData;
    Direction direction;
    OperationSize size;
    uint16_t registerMask;
};


} //namespace m68k::InstructionData