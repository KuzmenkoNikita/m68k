#pragma once
#include <cpu/internal/instructions/data/addressing_mode_instruction_data.h>
#include <cpu/internal/instructions/instruction_params.h>
#include <variant>

namespace m68k::InstructionData {

struct ORI_InstructionData {

    OperationSize size;

    std::variant<DataRegisterModeData,
                AddressModeData,
                AddressWithPostincrementModeData,
                AddressWithPredecrementModeData,
                AddressWithDisplacementModeData,
                AddressWithIndexModeData,
                AbsoluteShortModeData,
                AbsoluteLongModeData>  addressingModeData;

    union {
        uint8_t byteData;
        uint16_t wordData;
        uint32_t longData;
    } immediateFiles;
    
};    

} // namespace m68k::InstructionData