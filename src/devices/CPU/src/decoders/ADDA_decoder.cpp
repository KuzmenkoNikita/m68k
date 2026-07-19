#include <expected>
#include <instruction_decoder/decoders/ADDA_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>
#include <optional>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t ADDR_REGISTER_MASK = 0x0E00U;
constexpr uint16_t OPMODE_MASK = 0x01C0U;
constexpr uint16_t REGISTER_MASK = 0x0007U;
constexpr uint16_t MODE_MASK = 0x0038U;

} //namespace

ADDA_Decoder::ADDA_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> ADDA_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::ADDA_InstructionData instructionData{};

    instructionData.destinationAddressRegister = (opcodeWord & ADDR_REGISTER_MASK) >> 9U; //NOLINT

    const auto opmode = (opcodeWord & OPMODE_MASK) >> 6U; //NOLINT

    switch(opmode) {
        case 3: instructionData.size = OperationSize::WORD; break;
        case 7: instructionData.size = OperationSize::LONG; break; //NOLINT
        default: return std::unexpected(DecodeError::INVALID_INSTRUCTION_SIZE);
    }

    const uint8_t registerValue = opcodeWord & REGISTER_MASK;
    const uint8_t modeValue = (opcodeWord & MODE_MASK) >> 3U; //NOLINT

    const auto addressingMode = getAddressingMode(modeValue, registerValue);
    if(!addressingMode) {
        return std::unexpected(addressingMode.error());
    }

    GetAddressingModeDataParams getAddressingModeParams {
        .opSize = instructionData.size,
        .addressingMode = addressingMode.value(),
        .registerValue = registerValue,
        .instructionStartAddr = instructionStartAddr
    };

    const auto addressingModeData = getAddressingModeData(*bus_, getAddressingModeParams);
    if(!addressingModeData) {
        return std::unexpected(addressingModeData.error());
    }

    const auto convertedAddressingModeData = convertAddressingModeData<InstructionData::ADDA_InstructionData::AddressingModeData>(addressingModeData->data);
    if(!convertedAddressingModeData) {
        return std::unexpected(DecodeError::INVALID_ADDRESSING_MODE);
    }

    instructionData.sourceOperand = *convertedAddressingModeData;

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(addressingModeData.value().bytesReaded + sizeof(opcodeWord))
    };
}


} // namespace m68k::decoders_