#include "instructions/instruction_params.h"
#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/MOVE_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t SRC_MODE_MASK = 0b0011'1000U;
constexpr uint16_t SRC_REGISTER_MASK = 0b111U;

constexpr uint16_t DST_MODE_MASK = 0b1'1100'0000U;
constexpr uint16_t DST_REGISTER_MASK = 0b1110'0000'0000U;

constexpr uint16_t SIZE_MASK = 0b11'0000'0000'0000U;

} //namespace


MOVE_Decoder::MOVE_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> MOVE_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::MOVE_InstructionData instructionData{};

    const auto sizeValue = (opcodeWord & SIZE_MASK) >> 12U; //NOLINT

    switch(sizeValue) {
        case 0b01: instructionData.size = OperationSize::BYTE;
        case 0b11: instructionData.size = OperationSize::WORD;
        case 0b10: instructionData.size = OperationSize::LONG;
        default: return std::unexpected(DecodeError::INVALID_INSTRUCTION_SIZE);
    }

    const uint8_t srcRegisterValue = (opcodeWord & SRC_REGISTER_MASK);
    const uint8_t srcModeValue = (opcodeWord & SRC_MODE_MASK) >> 3U; //NOLINT

    const auto srcAddressingMode = getAddressingMode(srcModeValue, srcRegisterValue);
    if(!srcAddressingMode) {
        return std::unexpected(srcAddressingMode.error());
    }

    GetAddressingModeDataParams getAddressingModeParams {
        .opSize = instructionData.size,
        .addressingMode = srcAddressingMode.value(),
        .registerValue = srcRegisterValue,
        .addressingModeDataStartAddr = static_cast<uint32_t>(instructionStartAddr + sizeof(opcodeWord))
    };

    const auto srcAddressingModeData = getAddressingModeData(*bus_, getAddressingModeParams);
    if(!srcAddressingModeData) {
        return std::unexpected(srcAddressingModeData.error());
    }

    const auto convertedSrcAddressingModeData = convertAddressingModeData<InstructionData::MOVE_InstructionData::SrcAddressingModeData>(srcAddressingModeData->data);
    if(!convertedSrcAddressingModeData) {
        return std::unexpected(DecodeError::INVALID_ADDRESSING_MODE);
    }

    instructionData.sourceAddressingModeData = *convertedSrcAddressingModeData;

    const uint8_t dstRegisterValue = (opcodeWord & DST_REGISTER_MASK);
    const uint8_t dstModeValue = (opcodeWord & DST_MODE_MASK) >> 3U; //NOLINT

    const auto dstAddressingMode = getAddressingMode(dstModeValue, dstRegisterValue);
    if(!dstAddressingMode) {
        return std::unexpected(dstAddressingMode.error());
    }

    GetAddressingModeDataParams getDstAddressingModeParams {
        .opSize = instructionData.size,
        .addressingMode = dstAddressingMode.value(),
        .registerValue = dstRegisterValue,
        .addressingModeDataStartAddr = static_cast<uint32_t>(instructionStartAddr + sizeof(opcodeWord) + srcAddressingModeData->bytesReaded)
    };

    const auto dstAddressingModeData = getAddressingModeData(*bus_, getDstAddressingModeParams);
    if(!dstAddressingModeData) {
        return std::unexpected(dstAddressingModeData.error());
    }

    const auto convertedDstAddressingModeData = convertAddressingModeData<InstructionData::MOVE_InstructionData::DstAddressingModeData>(dstAddressingModeData->data);
    if(!convertedDstAddressingModeData) {
        return std::unexpected(DecodeError::INVALID_ADDRESSING_MODE);
    }

    instructionData.destinationAddressingModeData = *convertedDstAddressingModeData;

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(dstAddressingModeData->bytesReaded + srcAddressingModeData->bytesReaded + sizeof(opcodeWord))
    };

}

} // namespace m68k::decoders_