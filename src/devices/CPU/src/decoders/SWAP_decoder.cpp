#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/SWAP_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t REGISTER_MASK = 0b111U;

} //namespace

SWAP_Decoder::SWAP_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> SWAP_Decoder::decode(uint16_t opcodeWord, uint32_t /*instructionStartAddr*/) const
{
    InstructionData::SWAP_InstructionData instructionData{};

    instructionData.dataRegNumber = (opcodeWord & REGISTER_MASK);

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(sizeof(opcodeWord))
    };
}

} // namespace m68k::decoders_