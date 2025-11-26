#pragma once
#include <cstdint>

namespace m68k {

enum class DecodeError : uint8_t {
    INVALID_REGISTER_VALUE,
    INVALID_MODE_VALUE,
    INVALID_ADDRESSING_MODE,
    INVALID_INSTRUCTION,
    MEMORY_READ_FAILURE
};

} //namespace m68k