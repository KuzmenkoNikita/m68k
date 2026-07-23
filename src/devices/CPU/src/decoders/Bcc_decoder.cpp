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

    const auto conditionValue = (opcodeWord & CONDITION_MASK) >> 8U; //NOLINT

    switch(conditionValue) {
        case 0b0000: instructionData.condition = Condition::TRUE; break;
        case 0b0001: instructionData.condition = Condition::FALSE; break;
        case 0b0010: instructionData.condition = Condition::HIGH; break;
        case 0b0011: instructionData.condition = Condition::LOW_OR_SAME; break;
        case 0b0100: instructionData.condition = Condition::CARRY_CLEAR; break;
        case 0b0101: instructionData.condition = Condition::CARRY_SET; break;
        case 0b0110: instructionData.condition = Condition::NOT_EQUAL; break;
        case 0b0111: instructionData.condition = Condition::EQUAL; break;
        case 0b1000: instructionData.condition = Condition::OVERFLOW_CLEAR; break;
        case 0b1001: instructionData.condition = Condition::OVERFLOW_SET; break;
        case 0b1010: instructionData.condition = Condition::PLUS; break;
        case 0b1011: instructionData.condition = Condition::MINUS; break;
        case 0b1100: instructionData.condition = Condition::GREATER_OR_EQUAL; break;
        case 0b1101: instructionData.condition = Condition::LESS_THAN; break;
        case 0b1110: instructionData.condition = Condition::GREATER_THAN; break;
        case 0b1111: instructionData.condition = Condition::LESS_OR_EQUAL; break;
        default: return std::unexpected(DecodeError::INVALID_INSTRUCTION);
    }

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