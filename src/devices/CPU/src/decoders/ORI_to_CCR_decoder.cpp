#include <expected>
#include <instruction_decoder/decoders/ORI_to_CCR_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {
constexpr uint16_t IMMEDIATE_VALUE_MASK = 0x00FFU;
} //namespace


ORI_to_CCR_Decoder::ORI_to_CCR_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> ORI_to_CCR_Decoder::decode(uint16_t /*opcodeWord*/, uint32_t instructionStartAddr) const
{
    const auto readResult = bus_->read16(instructionStartAddr + 2);
    if(!readResult) {
        return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
    }

    InstructionData::ORI_to_CCR_InstructionData instructionData {
        .immediateData = static_cast<uint8_t>(readResult.value().data & IMMEDIATE_VALUE_MASK)
    };

    return DecodeResult{
        .instruction = instructionData
    };
}


} //namespace m68k::decoders_ 