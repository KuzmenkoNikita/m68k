#include <expected>
#include <instruction_decoder/decoders/ABCD_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t RX_MASK = 0x0E00;
constexpr uint16_t RY_MASK = 0x0007;
constexpr uint16_t RM_MASK = 0x0008;

} //namespace

ABCD_Decoder::ABCD_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> ABCD_Decoder::decode(uint16_t opcodeWord, uint32_t /*instructionStartAddr*/) const
{
   InstructionData::ABCD_InstructionData instructionData{};

   uint16_t rmValue = (opcodeWord & RM_MASK) >> 3U; //NOLINT

    switch(rmValue) {
        case 0: instructionData.operandAddressingMode = OperandAddressingMode::DATA_REG_TO_DATA_REG; break;
        case 1: instructionData.operandAddressingMode = OperandAddressingMode::MEM_TO_MEM; break;
        default: return std::unexpected(DecodeError::INVALID_INSTRUCTION);
    }

    instructionData.destinationRegister = opcodeWord & RY_MASK;
    instructionData.sourceRegister = (opcodeWord & RX_MASK) >> 9U; //NOLINT

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = sizeof(opcodeWord)
    };
}


} // namespace m68k::decoders_