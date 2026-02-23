#include <expected>
#include <instruction_decoder/decoders/decoders_helpers.h>
#include <instruction_decoder/decoders/tst_decoder.h>
#include <utility>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t SIZE_MASK = 0x00C0U;
constexpr uint16_t MODE_MASK = 0x0038U;
constexpr uint16_t REGISTER_MASK = 0x0007U;

} //namespace

TSTDecoder::TSTDecoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> TSTDecoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::TSTInstructionData instructionData;
    uint8_t sizeValue = (opcodeWord & SIZE_MASK) >> 6U; //NOLINT
    
    switch(sizeValue) {
        case 0: instructionData.size = OperationSize::BYTE; break;
        case 1: instructionData.size = OperationSize::WORD; break;
        case 2: instructionData.size = OperationSize::LONG; break;
        default: {
            return std::unexpected(DecodeError::INVALID_INSTRUCTION);
        }
    }

    uint8_t modeValue = (opcodeWord & MODE_MASK) >> 3U; //NOLINT
    uint8_t registerValue = (opcodeWord & REGISTER_MASK); //NOLINT

    const auto addressingMode = m68k::decoders_::getAddressingMode(modeValue, registerValue);
    if(!addressingMode) {
        return std::unexpected(addressingMode.error());
    }

    GetAddressingModeDataParams getAddressingModeParams {
        .opSize = instructionData.size,
        .addressingMode = addressingMode.value(),
        .registerValue = registerValue,
        .instructionStartAddr = instructionStartAddr
    };

    const auto addressingModeData = m68k::decoders_::getAddressingModeData(*bus_, getAddressingModeParams);
    if(!addressingModeData) {
        return std::unexpected(addressingModeData.error());
    }

    instructionData.addressingModeData = addressingModeData.value().data;

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(addressingModeData.value().bytesReaded + sizeof(opcodeWord))
    };
}

} // namespace m68k::decoders_