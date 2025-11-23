#pragma once
#include <cpu/internal/instruction_executor/base_executor.h>
#include <memory>
#include <memoryinterface.h>
#include <cpu/internal/registers.h>

namespace m68k::executors_ {

class TST_executor final : public IExecutor
{
public:
    TST_executor(std::shared_ptr<DataExchange::MemoryInterface> bus, std::shared_ptr<m68k_::Registers> registers);
    std::expected<void, ExecuteError> execute(const Instruction& instruction) override;
private:

    std::expected<void, ExecuteError> execute(const DataRegisterModeData& data, OperationSize size);
    std::expected<void, ExecuteError> execute(const AddressRegisterModeData& data, OperationSize size);
    std::expected<void, ExecuteError> execute(const AddressModeData& data, OperationSize size);
    std::expected<void, ExecuteError> execute(const AddressWithPostincrementModeData& data, OperationSize size);
    std::expected<void, ExecuteError> execute(const AddressWithPredecrementModeData& data, OperationSize size);
    std::expected<void, ExecuteError> execute(const AddressWithDisplacementModeData& data, OperationSize size);
    std::expected<void, ExecuteError> execute(const AddressWithIndexModeData& data, OperationSize size);
    std::expected<void, ExecuteError> execute(const ProgramCounterWithDisplacementModeData& data, OperationSize size);
    std::expected<void, ExecuteError> execute(const ProgramCounterWithIndexModeData& data, OperationSize size);
    std::expected<void, ExecuteError> execute(const AbsoluteShortModeData& data, OperationSize size);
    std::expected<void, ExecuteError> execute(const AbsoluteLongModeData& data, OperationSize size);
    std::expected<void, ExecuteError> execute(const ImmediateModeData& data, OperationSize size);

    void setConditionCodes(uint32_t value, OperationSize size);
private:
    std::shared_ptr<DataExchange::MemoryInterface> bus_;
    std::shared_ptr<m68k_::Registers> registers_;
};


} //namespace m68k::executors_