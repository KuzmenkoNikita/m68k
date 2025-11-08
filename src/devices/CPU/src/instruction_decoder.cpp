#include <cpu/internal/instruction_decoder.h>
#include <cpu/internal/instruction_params.h>

namespace m68k {

InstructionDecoder::InstructionDecoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<Instruction, InstructionDecoder::DecodeError> InstructionDecoder::decode(uint32_t pc) //NOLINT(*-identifier-length)
{
    return {};
}

} // namespace m68k