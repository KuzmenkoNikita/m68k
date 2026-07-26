#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/EORI_to_CCR_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {


EORI_to_CCR_Decoder::EORI_to_CCR_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> EORI_to_CCR_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::EORI_to_CCR_InstructionData instructionData{};

    const auto readResult = m68k::busHelper::read<uint8_t>(*bus_, instructionStartAddr + sizeof(opcodeWord));
    if(!readResult) {
        return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
    }

    instructionData.immediateData = readResult->data;

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(2 + sizeof(opcodeWord))
    };

}

} // namespace m68k::decoders_