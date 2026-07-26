#include <expected>
#include <instruction_decoder/decoders/Bcc_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>
#include <bus_helper/bus_helper.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t CONDITION_MASK = 0x0F00U;
constexpr uint16_t DISPLACEMENT_MASK = 0x00FFU;


} //namespace

Bcc_Decoder::Bcc_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> Bcc_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::Bcc_InstructionData instructionData{};

    const auto condition = getCondition((opcodeWord & CONDITION_MASK) >> 8U); //NOLINT
    if(!condition) {
        return std::unexpected(condition.error());
    }

    instructionData.condition = *condition;

    const auto displacement8bitValue = (opcodeWord & DISPLACEMENT_MASK);

    uint32_t bytesReaded = 0;

    if(displacement8bitValue == 0) {

        const auto readResult = m68k::busHelper::read<int16_t>(*bus_, instructionStartAddr + 2);
        if(!readResult) {
            return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
        }

        bytesReaded = 2;
        instructionData.displacement = readResult->data;
    } else if (displacement8bitValue == 0xFF) {

        const auto readResult = m68k::busHelper::read<int32_t>(*bus_, instructionStartAddr + 2);
        if(!readResult) {
            return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
        }

        bytesReaded = 4;
        instructionData.displacement = readResult->data;        
    } else {
        instructionData.displacement = static_cast<int32_t>(static_cast<int8_t>(displacement8bitValue));
    }

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(sizeof(opcodeWord) + bytesReaded)
    };
}


} // namespace m68k::decoders_