#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/ANDI_to_SR_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {
    
constexpr uint16_t SIZE_MASK = 0x00C0U;
constexpr uint16_t MODE_MASK = 0x0038U;
constexpr uint16_t REGISTER_MASK = 0x0007U;

} //namespace

ANDI_to_SR_Decoder::ANDI_to_SR_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> ANDI_to_SR_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::ANDI_to_SR_InstructionData instructionData{};

    const auto readResult = m68k::busHelper::read<uint16_t>(*bus_, instructionStartAddr + 2);
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