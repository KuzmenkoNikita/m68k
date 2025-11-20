#include "cpu/cpu.h"
#include "cpu/internal/registers.h"

namespace m68k {

CPU::CPU(std::shared_ptr<DataExchange::MemoryInterface> bus) :  bus_(std::move(bus)), 
                                                                regs_{},
                                                                instructionDecoder_(std::make_unique<InstructionDecoder>(bus_))
{

}

void CPU::reset()
{
    regs_.sr.supervisorOrUserState = true;
    regs_.sr.interruptMask = 0b111; //NOLINT
    
    auto readResult = read32(0); //NOLINT
    if (!readResult) {
        throw std::runtime_error("Failed to read initial PC from bus during CPU reset.");
    }

    regs_.ssp = readResult->data;

    readResult = read32(4); //NOLINT
    if (!readResult) {
        throw std::runtime_error("Failed to read initial PC from bus during CPU reset.");
    }

    regs_.pc = readResult->data;
}

std::expected<CPU::MemoryAccessResult, DataExchange::MemoryAccessError> CPU::read32(uint32_t address)
{
    auto highResult = bus_->read16(address);
    if (!highResult) {
        return std::unexpected(highResult.error());
    }

    auto lowResult = bus_->read16(address + 2);
    if (!lowResult) {
        return std::unexpected(lowResult.error());
    }

    return CPU::MemoryAccessResult{
        .data = (static_cast<uint32_t>(highResult->data) << 16U) | static_cast<uint32_t>(lowResult->data),
        .waitCycles = highResult->waitCycles + lowResult->waitCycles
    };
}

void CPU::executeNextInstruction()
{
    auto decodeResult = instructionDecoder_->decode(regs_.pc);
    int a = 0;
}

} // namespace m68k