#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/SBCD_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t SRC_REGISTER_MASK = 0b111U;
constexpr uint16_t DST_REGISTER_MASK = 0b1110'0000'0000U;
constexpr uint16_t RM_MASK = 0b1000U;


} //namespace

SBCD_Decoder::SBCD_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> SBCD_Decoder::decode(uint16_t opcodeWord, uint32_t /*instructionStartAddr*/) const
{
    InstructionData::SBCD_InstructionData instructionData{};

    instructionData.sourceRegister = (opcodeWord & SRC_REGISTER_MASK);
    instructionData.destinationRegister = (opcodeWord & DST_REGISTER_MASK) >> 9U; //NOLINT
    instructionData.operandAddressingMode = (opcodeWord & RM_MASK) != 0 ? OperandAddressingMode::MEM_TO_MEM : OperandAddressingMode::DATA_REG_TO_DATA_REG;

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(sizeof(opcodeWord))
    };
}

} // namespace m68k::decoders_