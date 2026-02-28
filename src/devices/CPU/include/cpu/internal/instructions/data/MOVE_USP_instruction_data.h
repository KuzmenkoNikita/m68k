#pragma once
#include <cstdint>

namespace m68k::InstructionData {


struct MOVE_USP_InstructionData {

    enum class Direction : uint8_t {
        ADDR_TO_USP,
        USP_TO_ADDR
    };

    Direction direction;
    uint8_t regNumber;
};


} //namespace m68k::InstructionData