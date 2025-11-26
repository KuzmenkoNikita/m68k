#include "instructions/data/ORI_instruction_data.h"
#include <expected>
#include <instruction_decoder/decoders/ORI_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t SIZE_MASK = 0x00C0U;
constexpr uint16_t MODE_MASK = 0x0038U;
constexpr uint16_t REGISTER_MASK = 0x0007U;

template<typename T>
concept AssignableAddressModeData = 
    std::is_same_v<T, DataRegisterModeData> ||
    std::is_same_v<T, AddressModeData> ||
    std::is_same_v<T, AddressWithPostincrementModeData> ||
    std::is_same_v<T, AddressWithPredecrementModeData> ||
    std::is_same_v<T, AddressWithDisplacementModeData> ||
    std::is_same_v<T, AddressWithIndexModeData> ||
    std::is_same_v<T, AbsoluteShortModeData> ||
    std::is_same_v<T, AbsoluteLongModeData>;

} //namespace



ORI_Decoder::ORI_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> ORI_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    uint8_t sizeValue = static_cast<uint8_t>(opcodeWord & SIZE_MASK) >> 6U; //NOLINT
    uint8_t modeValue = static_cast<uint8_t>(opcodeWord & MODE_MASK) >> 3U; //NOLINT
    uint8_t registerValue = static_cast<uint8_t>(opcodeWord & REGISTER_MASK); //NOLINT

    InstructionData::ORI_InstructionData instructionData;

    switch(sizeValue) {
        case 0: instructionData.size = OperationSize::BYTE; break;
        case 1: instructionData.size = OperationSize::WORD; break;
        case 2: instructionData.size = OperationSize::LONG; break;
        default: {
            return std::unexpected(DecodeError::INVALID_INSTRUCTION);
        }
    }

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

    auto addressingModeResult = std::visit([&instructionData]<typename T>(const T& data) -> bool {
        if constexpr (AssignableAddressModeData<T>) {
            instructionData.addressingModeData = data;
            return true;
        } 
            
        return false;
        
    }, addressingModeData->data);

    if(!addressingModeResult) {
        return std::unexpected(DecodeError::INVALID_INSTRUCTION);
    }

    uint32_t bytesReaded = sizeof(opcodeWord) + addressingModeData->bytesReaded;

    auto firtstWordReadResult = bus_->read16(instructionStartAddr + bytesReaded);
    if(!firtstWordReadResult) {
        return std::unexpected(DecodeError::MEMORY_READ_FAILURE); 
    }

    bytesReaded += 2;
    switch(instructionData.size) 
    {
        case OperationSize::BYTE: 
        {
            instructionData.immediateFiles.byteData = static_cast<uint8_t>(firtstWordReadResult->data & 0x00FFU);
            break;
        }

        case OperationSize::WORD: 
        {
            instructionData.immediateFiles.wordData = firtstWordReadResult->data;
            break;
        }

        case OperationSize::LONG: 
        {
            auto secondWordReadResult = bus_->read16(instructionStartAddr + bytesReaded);
            if (!secondWordReadResult) {
                return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
            }

            bytesReaded += 2;
            instructionData.immediateFiles.longData = (static_cast<uint32_t>(firtstWordReadResult->data) << 16U) | static_cast<uint32_t>(secondWordReadResult->data);
            break;
        }

        default: return std::unexpected(DecodeError::INVALID_INSTRUCTION);
    }

    return DecodeResult{
        .instruction = instructionData,
        .instructionSizeBytes = bytesReaded
    };
}


} //namespace m68k::decoders_ 