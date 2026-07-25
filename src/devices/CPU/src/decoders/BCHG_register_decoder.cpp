#include <expected>
#include <instruction_decoder/decoders/BCHG_register_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>
#include <bus_helper/bus_helper.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t DATA_REG_MASK = 0b0000'1110'0000'0000;
constexpr uint16_t MODE_MASK = 0b0011'1000;
constexpr uint16_t REGISTER_MASK = 0b111;

} //namespace

BCHG_Register_Decoder::BCHG_Register_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> BCHG_Register_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::BCHG_Register_InstructionData instructionData{};

    const auto dataRegisterValue = (opcodeWord & DATA_REG_MASK) >> 9U; //NOLINT

    instructionData.dataRegNumber = dataRegisterValue;

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
        .instructionStartAddr = instructionStartAddr
    };

    const auto addressingModeData = getAddressingModeData(*bus_, getAddressingModeParams);
    if(!addressingModeData) {
        return std::unexpected(addressingModeData.error());
    }

    const auto convertedAddressingModeData = convertAddressingModeData<InstructionData::BCHG_Register_InstructionData::AddressingModeData>(addressingModeData->data);
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