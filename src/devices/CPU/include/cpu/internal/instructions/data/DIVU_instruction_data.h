#pragma once
#include "addressing_mode_instruction_data.h"
#include <variant>

namespace m68k::InstructionData {


struct DIVU_InstructionData {

    uint8_t dataRegNumber;

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
    AddressingModeData addressingModeData;

};


} //namespace m68k::InstructionData