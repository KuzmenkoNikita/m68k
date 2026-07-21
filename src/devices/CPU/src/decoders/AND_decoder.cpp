#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/AND_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {
    
constexpr uint16_t DATA_REGISTER_MASK = 0x0E00U;
constexpr uint16_t OPMODE_MASK = 0x01C0U;
constexpr uint16_t MODE_MASK = 0x0038U;
constexpr uint16_t REGISTER_MASK = 0x0007U;

} //namespace

AND_Decoder::AND_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> AND_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::AND_InstructionData instructionData{};

    instructionData.dataRegisterNumber = (opcodeWord & DATA_REGISTER_MASK) >> 9U; //NOLINT

    const auto opmodeValue = (opcodeWord & OPMODE_MASK) >> 6U; //NOLINT

    switch(opmodeValue) {

        case 0: {
            instructionData.size = OperationSize::BYTE;
            instructionData.destOperandType = DestinationOperandType::DESTINATION_DN;
            break;
        }

        case 1: {
            instructionData.size = OperationSize::WORD;
            instructionData.destOperandType = DestinationOperandType::DESTINATION_DN;
            break;
        }

        case 2: {
            instructionData.size = OperationSize::LONG;
            instructionData.destOperandType = DestinationOperandType::DESTINATION_DN;
            break;
        }

        case 4: {
            instructionData.size = OperationSize::BYTE;
            instructionData.destOperandType = DestinationOperandType::DESTINATION_EA;
            break;
        }

        case 5: {   //NOLINT
            instructionData.size = OperationSize::WORD;
            instructionData.destOperandType = DestinationOperandType::DESTINATION_EA;
            break;
        }

        case 6: {   //NOLINT
            instructionData.size = OperationSize::LONG;
            instructionData.destOperandType = DestinationOperandType::DESTINATION_EA;
            break;
        }

        default: return std::unexpected(DecodeError::INVALID_OPMODE);
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

    const auto convertedAddressingModeData = convertAddressingModeData<InstructionData::AND_InstructionData::AddressingModeData>(addressingModeData->data);
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