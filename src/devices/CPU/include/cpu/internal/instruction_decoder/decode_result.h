#pragma once
#include <cpu/internal/instructions/instruction.h>

namespace m68k {

struct DecodeResult {
    Instruction instruction;
    uint32_t    instructionSizeBytes{};
};

} //namespace m68k