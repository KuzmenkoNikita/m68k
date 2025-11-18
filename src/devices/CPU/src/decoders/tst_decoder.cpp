#include <expected>
#include <instruction_decoder/decoders/tst_decoder.h>

#include <utility>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t SIZE_MASK = 0x00C0U;
constexpr uint16_t MODE_MASK = 0x0038U;
constexpr uint16_t REGISTER_MASK = 0x0007U;

} //namespace

TSTDecoder::TSTDecoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : BaseDecoder(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> TSTDecoder::decodeImpl(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::TSTInstructionData instructionData;
    uint8_t sizeValue = (opcodeWord & SIZE_MASK) >> 6U; //NOLINT
    
    switch(sizeValue) {
        case 0: instructionData.size = InstructionData::TSTInstructionData::Size::BYTE; break;
        case 1: instructionData.size = InstructionData::TSTInstructionData::Size::WORD; break;
        case 2: instructionData.size = InstructionData::TSTInstructionData::Size::LONG; break;
        default: {
            return std::unexpected(DecodeError::INVALID_INSTRUCTION);
        }
    }

    uint8_t modeValue = (opcodeWord & MODE_MASK) >> 3U; //NOLINT
    uint8_t registerValue = (opcodeWord & REGISTER_MASK); //NOLINT

    uint32_t instructionSize = 2;


    return std::unexpected(DecodeError::INVALID_INSTRUCTION);
}

} // namespace m68k::decoders_