#pragma once
#include <cstdint>

namespace m68k {

enum class ExecuteError : uint8_t {
    MEMORY_READ_FAILURE,
    INVALID_INSTRUCTION,
    INVALID_OPERATION_SIZE
};

} //namespace m68k
