#include "instructions/instruction_params.h"
#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/SUBQ_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t REGISTER_MASK = 0b111U;
constexpr uint16_t MODE_MASK = 0b11'1000U;
constexpr uint16_t SIZE_MASK = 0b1100'0000U;
constexpr uint16_t DATA_MASK = 0b1110'0000'0000U;


} //namespace

SUBQ_Decoder::SUBQ_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> SUBQ_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::SUBQ_InstructionData instructionData{};

    instructionData.data = (opcodeWord & DATA_MASK) >> 9U; //NOLINT
    if(instructionData.data == 0) {
        instructionData.data = 8;
    }

    const auto sizeValue = (opcodeWord & SIZE_MASK) >> 6U; //NOLINT

    switch(sizeValue) {

        case 0b00: {
            instructionData.size = OperationSize::BYTE; 
            break;
        }

        case 0b01: {
            instructionData.size = OperationSize::WORD; 
            break;
        }

        case 0b10: {
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
        .addressingModeDataStartAddr = static_cast<uint32_t>(instructionStartAddr + sizeof(opcodeWord))
    };

    const auto addressingModeData = getAddressingModeData(*bus_, getAddressingModeParams);
    if(!addressingModeData) {
        return std::unexpected(addressingModeData.error());
    }

    const auto convertedAddressingModeData = convertAddressingModeData<InstructionData::SUBQ_InstructionData::AddressingModeData>(addressingModeData->data);
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