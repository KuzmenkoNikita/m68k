#pragma once
#include <cpu/internal/instruction_executor/instruction_execute_error.h>
#include <cpu/internal/instructions/instruction.h>
#include <expected>

namespace m68k::executors_ {

class IExecutor 
{
public:
    virtual ~IExecutor() = default;
    virtual std::expected<void, ExecuteError> execute(const Instruction& instruction) = 0;
};

} //namespace m68k::executors_