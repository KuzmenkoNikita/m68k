#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/MOVEP_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t ADDR_REG_MASK = 0b111U;
constexpr uint16_t OPMODE_MASK = 0b1'1100'0000U;
constexpr uint16_t DATA_REG_MASK = 0b1110'0000'0000U;

} //namespace


MOVEP_Decoder::MOVEP_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> MOVEP_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::MOVEP_InstructionData instructionData{};

    instructionData.dataRegNumber = (opcodeWord & DATA_REG_MASK) >> 9U; //NOLINT
    instructionData.addrRegNumber = (opcodeWord & ADDR_REG_MASK);

    const auto opmodeValue = (opcodeWord & OPMODE_MASK) >> 6U; //NOLINT

    switch(opmodeValue) {
        case 0b100: instructionData.mode = InstructionData::MOVEP_InstructionData::OpMode::WORD_MEM_TO_REG; break;
        case 0b101: instructionData.mode = InstructionData::MOVEP_InstructionData::OpMode::LONG_MEM_TO_REG; break;
        case 0b110: instructionData.mode = InstructionData::MOVEP_InstructionData::OpMode::WORD_REG_TO_MEM; break;
        case 0b111: instructionData.mode = InstructionData::MOVEP_InstructionData::OpMode::LONG_REG_TO_MEM; break;
        default: return std::unexpected(DecodeError::INVALID_OPMODE);
    }

    const auto readResult = m68k::busHelper::read<int16_t>(*bus_, instructionStartAddr + sizeof(opcodeWord));
    if(!readResult) {
        return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
    }

    instructionData.displacement = readResult->data;

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(2 + sizeof(opcodeWord))
    };
}

} // namespace m68k::decoders_