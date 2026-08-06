#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/MOVEQ_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t DATA_MASK = 0b1111'1111U;
constexpr uint16_t REG_MASK = 0b1110'0000'0000;


} //namespace


MOVEQ_Decoder::MOVEQ_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> MOVEQ_Decoder::decode(uint16_t opcodeWord, uint32_t /*instructionStartAddr*/) const
{
    InstructionData::MOVEQ_InstructionData instructionData{};
    instructionData.data = static_cast<int8_t>(opcodeWord & DATA_MASK);
    instructionData.dataRegNumber = (opcodeWord & REG_MASK) >> 9U; //NOLINT

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(sizeof(opcodeWord))
    };
}

} // namespace m68k::decoders_