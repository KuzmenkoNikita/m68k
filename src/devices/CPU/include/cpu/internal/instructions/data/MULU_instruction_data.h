#pragma once
#include "addressing_mode_instruction_data.h"
#include <variant>

namespace m68k::InstructionData {


struct MULU_InstructionData {

    using AddressingModeData = std::variant<DataRegisterModeData,
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
    AddressingModeData sourceOperand;
    uint8_t destinationDataRegister;
};


} //namespace m68k::InstructionData