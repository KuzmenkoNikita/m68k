#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/CHK_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t DATA_REG_MASK = 0b0000'1110'0000'0000U;
constexpr uint16_t MODE_MASK = 0b0011'1000U;
constexpr uint16_t REGISTER_MASK = 0b111U;
constexpr uint16_t SIZE_MASK = 0b1'1000'0000U;

} //namespace

CHK_Decoder::CHK_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> CHK_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::CHK_InstructionData instructionData{};

    instructionData.dataRegNumber = (opcodeWord & DATA_REG_MASK) >> 9U; //NOLINT

    const auto sizeValue = (opcodeWord & SIZE_MASK) >> 7U; //NOLINT

    switch(sizeValue) {
        case 0b11: instructionData.size = OperationSize::WORD;
        case 0b10: instructionData.size = OperationSize::LONG;   
        default: return std::unexpected(DecodeError::INVALID_INSTRUCTION_SIZE);
    }

    const uint8_t registerValue = opcodeWord & REGISTER_MASK;
    const uint8_t modeValue = (opcodeWord & MODE_MASK) >> 3U; //NOLINT

    const auto addressingMode = getAddressingMode(modeValue, registerValue);
    if(!addressingMode) {
        return std::unexpected(addressingMode.error());
    }

    GetAddressingModeDataParams getAddressingModeParams {
        .opSize = OperationSize::WORD,
        .addressingMode = addressingMode.value(),
        .registerValue = registerValue,
        .addressingModeDataStartAddr = static_cast<uint32_t>(instructionStartAddr + sizeof(opcodeWord))
    };

    const auto addressingModeData = getAddressingModeData(*bus_, getAddressingModeParams);
    if(!addressingModeData) {
        return std::unexpected(addressingModeData.error());
    }

    const auto convertedAddressingModeData = convertAddressingModeData<InstructionData::CHK_InstructionData::AddressingModeData>(addressingModeData->data);
    if(!convertedAddressingModeData) {
        return std::unexpected(DecodeError::INVALID_ADDRESSING_MODE);
    }

    instructionData.addressingModeData = *convertedAddressingModeData;

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(addressingModeData.value().bytesReaded + sizeof(opcodeWord))
    };
}


} // namespace m68k::decoders_