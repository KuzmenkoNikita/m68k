#pragma once
#include <cstdint>

namespace m68k::InstructionData {


struct EXG_InstructionData {

    enum class ExchaneType : uint8_t {
        DATA_REG,
        ADDRESS_REG,
        DATA_REG_AND_ADDRESS_REG
    };

    ExchaneType exchangeType;
    uint8_t registerRx;
    uint8_t registerRy;
};


} //namespace m68k::InstructionData