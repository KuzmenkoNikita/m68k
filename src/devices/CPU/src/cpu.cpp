#include "cpu/cpu.h"
#include "cpu/internal/registers.h"

namespace m68k {

CPU::CPU(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus)), regs_{}
{

}

void CPU::reset()
{
    regs_.sr.supervisorOrUserState = true;
    regs_.sr.interruptMask = 0b111; //NOLINT
    
    auto readResult = bus_->read16(0); //NOLINT
    if (!readResult) {
        throw std::runtime_error("Failed to read initial PC from bus during CPU reset.");
    }

    regs_.ssp = static_cast<uint32_t>(readResult->data) << 16; //NOLINT

    readResult = bus_->read16(2); //NOLINT
    if (!readResult) {
        throw std::runtime_error("Failed to read initial PC from bus during CPU reset.");
    }

    regs_.ssp |= static_cast<uint32_t>(readResult->data); //NOLINT
}

} // namespace m68k