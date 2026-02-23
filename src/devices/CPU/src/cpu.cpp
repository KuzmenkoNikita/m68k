#include "cpu/cpu.h"
#include "cpu/internal/registers.h"
#include "cpu/internal/instruction_executor/executors/TST_executor.h"
#include "cpu/internal/instruction_decoder/instruction_decoder.h"

namespace m68k {

CPU::CPU(std::shared_ptr<DataExchange::MemoryInterface> bus) :  bus_(std::move(bus)), 
                                                                regs_{},
                                                                instructionDecoder_(std::make_unique<InstructionDecoder>(bus_))
{

}

void CPU::reset()
{
    //regs_.SR().supervisorOrUserState = true;
    //regs_.SR().interruptMask = 0b111; //NOLINT
    //
    //auto readResult = read32(0); //NOLINT
    //if (!readResult) {
    //    throw std::runtime_error("Failed to read initial PC from bus during CPU reset.");
    //}
//
    //regs_.SSP() = readResult->data;
//
    //readResult = read32(4); //NOLINT
    //if (!readResult) {
    //    throw std::runtime_error("Failed to read initial PC from bus during CPU reset.");
    //}
//
    //regs_.PC() = readResult->data;
}

void CPU::initExecutors()
{
    executors_.reserve(static_cast<size_t>(InstructionType::INSTRUCTIONS_COUNT));
    for(auto i = 0; i < static_cast<size_t>(InstructionType::INSTRUCTIONS_COUNT); ++i) {
        executors_.emplace_back(std::nullopt);
    }

    executors_[static_cast<size_t>(InstructionType::TST)]= std::make_unique<executors_::TST_executor>(bus_, std::make_shared<m68k_::Registers>(regs_));
}


void CPU::executeNextInstruction()
{
    auto decodeResult = instructionDecoder_->decode(regs_.PC());
    if(!decodeResult) {
        throw std::runtime_error("Failed to decode instruction at PC: " + std::to_string(regs_.PC()));
    }

    const auto& instruction = decodeResult->instruction;
    auto& executorOpt = executors_.at(static_cast<size_t>(instruction.type()));
    if(!executorOpt.has_value()) {
        throw std::runtime_error("No executor for instruction at PC: " + std::to_string(regs_.PC()));
    }

    auto executeResult = executorOpt.value()->execute(instruction);
}

m68k_::Registers& CPU::registers()
{
    return regs_;
}

} // namespace m68k