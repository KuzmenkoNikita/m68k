#include <expected>
#include <instruction_decoder/decoders/ORI_to_SR_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {


ORI_to_SR_Decoder::ORI_to_SR_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> ORI_to_SR_Decoder::decode(uint16_t /*opcodeWord*/, uint32_t instructionStartAddr) const
{
    const auto readResult = bus_->read16(instructionStartAddr + 2);
    if(!readResult) {
        return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
    }

    InstructionData::ORI_to_SR_InstructionData instructionData {
        .immediateData = readResult.value().data
    };

    return DecodeResult{
        .instruction = instructionData
    };
}


} //namespace m68k::decoders_ 