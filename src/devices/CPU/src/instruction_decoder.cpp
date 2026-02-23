#include <bus_helper/bus_helper.h>
#include <instruction_decoder/decoders/tst_decoder.h>
#include <instruction_decoder/instruction_decoder.h>
#include <instructions/instruction_params.h>
#include <memory>
#include <optional>

namespace m68k {

InstructionDecoder::InstructionDecoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : 
                                    bus_(std::move(bus))
                                    , typeDecoder_(std::make_unique<InstructionTypeDecoder>())
{
    initDecoders();
}

std::expected<DecodeResult, DecodeError> InstructionDecoder::decode(uint32_t pc) //NOLINT(*-identifier-length)
{
    const auto readResult = m68k::busHelper::read<uint16_t>(*bus_, pc);
    if(!readResult){
        return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
    }

    auto instructionTypeResult = typeDecoder_->decode(readResult->data);
    if(!instructionTypeResult) {
        return std::unexpected(DecodeError::INVALID_INSTRUCTION);
    }

    return decoders_.at(static_cast<size_t>(instructionTypeResult.value())).value()->decode(readResult.value().data, pc);

}

void InstructionDecoder::initDecoders()
{
    decoders_.reserve(static_cast<size_t>(InstructionType::INSTRUCTIONS_COUNT));
    for(auto i = 0; i < static_cast<size_t>(InstructionType::INSTRUCTIONS_COUNT); ++i) {
        decoders_.emplace_back(std::nullopt);
    }

    decoders_[static_cast<size_t>(InstructionType::TST)]= std::make_unique<decoders_::TSTDecoder>(bus_);
}


} // namespace m68k