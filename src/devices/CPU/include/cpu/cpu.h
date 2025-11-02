#pragma once
#include "cpu/internal/registers.h"

namespace m68k {

class CPU {
public:
    explicit CPU();

private:
    m68k_::Registers regs_;
};

} // namespace m68k