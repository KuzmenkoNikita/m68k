#pragma once
#include <cstdint>

namespace m68k::InstructionData {


struct EXT_InstructionData {

    enum class OpMode : uint8_t {
        BYTE_TO_WORD,
        WORD_TO_LONG,
        BYTE_TO_LONG
    };

    OpMode opMode;
    uint8_t dataRegisterNumber;
};


} //namespace m68k::InstructionData