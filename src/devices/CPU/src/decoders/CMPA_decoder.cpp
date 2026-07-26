#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/CMPA_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t MODE_MASK = 0b0011'1000U;
constexpr uint16_t REGISTER_MASK = 0b111U;
constexpr uint16_t ADDRESS_REGISTER_MASK = 0b1110'0000'0000U;
constexpr uint16_t OPMODE_MASK = 0b1'1100'0000U;

} //namespace

CMPA_Decoder::CMPA_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> CMPA_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::CMPA_InstructionData instructionData{};

    instructionData.addressRegisterNumber = (opcodeWord & ADDRESS_REGISTER_MASK) >> 9U; //NOLINT 

    const auto opmodeValue = (opcodeWord & OPMODE_MASK) >> 6U; //NOLINT
    
    switch(opmodeValue) {
        case 0b011: instructionData.size = OperationSize::WORD; break;
        case 0b111: instructionData.size = OperationSize::LONG; break;
        default: return std::unexpected(DecodeError::INVALID_OPMODE);
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

    const auto convertedAddressingModeData = convertAddressingModeData<InstructionData::CMPA_InstructionData::AddressingModeData>(addressingModeData->data);
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