#pragma once
#include <cpu/internal/instructions/data/addressing_mode_instruction_data.h>
#include <cpu/internal/instructions/instruction_params.h>
#include <variant>

namespace m68k::InstructionData {

struct ORI_InstructionData {

    using AddressingModeData = std::variant<DataRegisterModeData,
                                            AddressModeData,
                                            AddressWithPostincrementModeData,
                                            AddressWithPredecrementModeData,
                                            AddressWithDisplacementModeData,
                                            AddressWithIndexModeData,
                                            AbsoluteShortModeData,
                                            AbsoluteLongModeData>;

    std::variant<uint8_t, uint16_t, uint32_t> immediateData;
    OperationSize size;
    AddressingModeData addressingModeData;
    
};    

} // namespace m68k::InstructionData