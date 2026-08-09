#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/STOP_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {


STOP_Decoder::STOP_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> STOP_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::STOP_InstructionData instructionData{};

    const auto readResult = m68k::busHelper::read<uint16_t>(*bus_, instructionStartAddr + sizeof(opcodeWord));
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