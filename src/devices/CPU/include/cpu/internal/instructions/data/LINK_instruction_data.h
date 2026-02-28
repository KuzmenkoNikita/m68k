#pragma once
#include <cstdint>

namespace m68k::InstructionData {

struct LINK_InstructionData {

    int16_t displacement;
    uint8_t addrRegisterNumber;
};


} //namespace m68k::InstructionData