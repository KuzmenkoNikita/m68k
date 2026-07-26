#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/CMPM_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t REGISTER_SRC_MASK = 0b111;
constexpr uint16_t REGISTER_DST_MASK = 0b1110'0000'0000;
constexpr uint16_t SIZE_MASK = 0b1100'0000;


} //namespace

CMPM_Decoder::CMPM_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> CMPM_Decoder::decode(uint16_t opcodeWord, uint32_t /*instructionStartAddr*/) const
{
    InstructionData::CMPM_InstructionData instructionData{};

    instructionData.sourceRegisterNumber = (opcodeWord & REGISTER_SRC_MASK); //NOLINT
    instructionData.destinationRegisterNumber = (opcodeWord & REGISTER_DST_MASK) >> 9U; //NOLINT

    switch((opcodeWord & SIZE_MASK) >> 6) { //NOLINT
        case 0b00: instructionData.size = OperationSize::BYTE; break; 
        case 0b01: instructionData.size = OperationSize::WORD; break; 
        case 0b10: instructionData.size = OperationSize::LONG; break; 
        default: return std::unexpected(DecodeError::INVALID_INSTRUCTION_SIZE);
    }

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = sizeof(opcodeWord)
    };
}


} // namespace m68k::decoders_