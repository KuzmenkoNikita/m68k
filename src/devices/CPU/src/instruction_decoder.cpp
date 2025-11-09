#include <cpu/internal/instruction_decoder.h>
#include <instruction_params.h>
#include <expected>

namespace m68k {

InstructionDecoder::InstructionDecoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : 
                                    bus_(std::move(bus))
                                    , typeDecoder_(std::make_unique<InstructionTypeDecoder>())
{

}

//std::expected<Instruction, DecodeError> InstructionDecoder::decode(uint32_t pc) //NOLINT(*-identifier-length)
//{
//    auto readResult = bus_->read16(pc);
//    if(!readResult){
//        return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
//    }
//
//    auto instructionTypeResult = typeDecoder_->decode(readResult->data);
//    if(!instructionTypeResult) {
//        return std::unexpected(DecodeError::INVALID_INSTRUCTION);
//    }
//
//    return {};
//}

} // namespace m68k