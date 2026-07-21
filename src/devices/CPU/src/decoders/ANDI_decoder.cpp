#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/ANDI_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {
    
constexpr uint16_t SIZE_MASK = 0x00C0U;
constexpr uint16_t MODE_MASK = 0x0038U;
constexpr uint16_t REGISTER_MASK = 0x0007U;

} //namespace

ANDI_Decoder::ANDI_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> ANDI_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::ANDI_InstructionData instructionData{};

    const auto sizeValue = (opcodeWord & SIZE_MASK) >> 6U; //NOLINT

    switch(sizeValue) {

        case 0 : {
            instructionData.size = OperationSize::BYTE; 
            break;
        }

        case 1 : {
            instructionData.size = OperationSize::WORD; 
            break;
        }

        case 2 : {
            instructionData.size = OperationSize::LONG; 
            break;
        }

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

    const auto convertedAddressingModeData = convertAddressingModeData<InstructionData::ANDI_InstructionData::AddressingModeData>(addressingModeData->data);
    if(!convertedAddressingModeData) {
        return std::unexpected(DecodeError::INVALID_ADDRESSING_MODE);
    }

    instructionData.addressingModeData = *convertedAddressingModeData;

    const auto immediateValueAddr = instructionStartAddr + addressingModeData->bytesReaded;
    uint32_t immediateBytesReaded = 0;
    switch(instructionData.size) {

        case OperationSize::BYTE: {

            const auto readResult = m68k::busHelper::read<uint8_t>(*bus_, immediateValueAddr);
            if(!readResult) {
                return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
            }

            instructionData.immediateData = readResult->data;
            immediateBytesReaded = 2;
            break;
        }

        case OperationSize::WORD: {

            const auto readResult = m68k::busHelper::read<uint16_t>(*bus_, immediateValueAddr);
            if(!readResult) {
                return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
            }

            instructionData.immediateData = readResult->data;
            immediateBytesReaded = 2;
            break;
        }

        case OperationSize::LONG: {

            const auto readResult = m68k::busHelper::read<uint32_t>(*bus_, immediateValueAddr);
            if(!readResult) {
                return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
            }

            instructionData.immediateData = readResult->data;
            immediateBytesReaded = 4;
            break;
        }

        default: {
            return std::unexpected(DecodeError::INVALID_INSTRUCTION);
        }
    }
    

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(addressingModeData.value().bytesReaded + immediateBytesReaded + sizeof(opcodeWord))
    };

}


} // namespace m68k::decoders_