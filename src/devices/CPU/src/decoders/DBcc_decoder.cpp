#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/DBcc_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t REGISTER_MASK = 0b111;
constexpr uint16_t CONDITION_MASK = 0b1111'0000'0000;


} //namespace

DBcc_Decoder::DBcc_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> DBcc_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::DBcc_InstructionData instructionData{};

    instructionData.registerNumber = (opcodeWord & REGISTER_MASK);

    const auto condition = getCondition((opcodeWord & CONDITION_MASK) >> 8U); //NOLINT
    if(!condition) {
        return std::unexpected(condition.error());
    }
    
    instructionData.condition = *condition;

    const auto readResult = m68k::busHelper::read<int16_t>(*bus_, instructionStartAddr + sizeof(opcodeWord));
    if(!readResult) {
        return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
    }

    instructionData.displacement = readResult->data;

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = sizeof(opcodeWord) + 2
    };
}

} // namespace m68k::decoders_