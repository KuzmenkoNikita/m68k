#pragma once
#include "cpu/internal/registers.h"
#include <memoryinterface.h>
#include <memory>

namespace m68k {

class CPU {
public:
    explicit CPU(std::shared_ptr<DataExchange::MemoryInterface> bus);

    void reset();

private:
    m68k_::Registers regs_;
    std::shared_ptr<DataExchange::MemoryInterface> bus_;
};

} // namespace m68k