#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/ADDX_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t SIZE_MASK = 0x00C0U;
constexpr uint16_t RX_MASK = 0x0E00U;
constexpr uint16_t RM_MASK = 0x0008U;
constexpr uint16_t RY_MASK = 0x0007U;

} //namespace

ADDX_Decoder::ADDX_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> ADDX_Decoder::decode(uint16_t opcodeWord, uint32_t /*instructionStartAddr*/) const
{
    InstructionData::ADDX_InstructionData instructionData{};

    instructionData.destinationRegister = (opcodeWord & RX_MASK) >> 9U; //NOLINT
    instructionData.sourceRegister = (opcodeWord & RY_MASK); //NOLINT

    const auto rmValue = (opcodeWord & RM_MASK) >> 3U; //NOLINT
    if(rmValue == 0) {
        instructionData.operandAddressingMode = OperandAddressingMode::DATA_REG_TO_DATA_REG; 
    } else if (rmValue == 1) {
        instructionData.operandAddressingMode = OperandAddressingMode::MEM_TO_MEM; 
    } else {
        return std::unexpected(DecodeError::INVALID_INSTRUCTION);
    }

    const auto size = (opcodeWord & SIZE_MASK) >> 6U; //NOLINT

    switch(size) {
        case 0: instructionData.size = OperationSize::BYTE; break;
        case 1: instructionData.size = OperationSize::WORD; break;
        case 2: instructionData.size = OperationSize::LONG; break; //NOLINT
        default: return std::unexpected(DecodeError::INVALID_INSTRUCTION_SIZE);
    }

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = sizeof(opcodeWord)
    };
}


} // namespace m68k::decoders_