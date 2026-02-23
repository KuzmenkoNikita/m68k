#pragma once
#include <cpu/internal/instruction_executor/base_executor.h>
#include <cpu/internal/instruction_decoder/instruction_decoder.h>
#include <cpu/internal/registers.h>
#include <memory>
#include <memoryinterface.h>

namespace m68k {

class CPU {
public:
    explicit CPU(std::shared_ptr<DataExchange::MemoryInterface> bus);

    void reset();

    void executeNextInstruction();

    m68k_::Registers& registers();
private:

    void initExecutors();

private:
    m68k_::Registers regs_;
    std::shared_ptr<DataExchange::MemoryInterface> bus_;
    std::unique_ptr<InstructionDecoder> instructionDecoder_;
    /// Временный optional, когда все декодеры будут реализованы, он будет убран
    std::vector<std::optional<std::unique_ptr<executors_::IExecutor>>> executors_;
};

} // namespace m68k