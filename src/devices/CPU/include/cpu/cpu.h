#pragma once
#include <cpu/internal/instruction_decoder.h>
#include <cpu/internal/registers.h>
#include <memory>
#include <memoryinterface.h>

namespace m68k {

class CPU {
public:
    explicit CPU(std::shared_ptr<DataExchange::MemoryInterface> bus);

    void reset();

    void executeNextInstruction();
private:

    struct MemoryAccessResult {
        uint32_t data;
        int waitCycles; 
    };

    std::expected<MemoryAccessResult, DataExchange::MemoryAccessError> read32(uint32_t address);

private:
    m68k_::Registers regs_;
    std::shared_ptr<DataExchange::MemoryInterface> bus_;
    std::unique_ptr<InstructionDecoder> instructionDecoder_;
};

} // namespace m68k