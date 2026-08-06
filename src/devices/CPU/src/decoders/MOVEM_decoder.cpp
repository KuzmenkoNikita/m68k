#include "instructions/instruction_params.h"
#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/MOVEM_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t MODE_MASK = 0b0011'1000U;
constexpr uint16_t REGISTER_MASK = 0b111U;
constexpr uint16_t SIZE_MASK = 0b100'0000U;
constexpr uint16_t DR_MASK = 0b100'0000'0000U;

} //namespace


MOVEM_Decoder::MOVEM_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> MOVEM_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::MOVEM_InstructionData instructionData{};

    instructionData.size = (opcodeWord & SIZE_MASK) != 0 ? OperationSize::LONG : OperationSize::WORD;
    instructionData.direction = (opcodeWord & DR_MASK) != 0 ?   InstructionData::MOVEM_InstructionData::Direction::MEM_TO_REG : 
                                                                InstructionData::MOVEM_InstructionData::Direction::REG_TO_MEM;

    const auto readResult = m68k::busHelper::read<uint16_t>(*bus_, instructionStartAddr + sizeof(opcodeWord));
    if(!readResult) {
        return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
    }
    
    instructionData.registerMask = readResult->data;

    const uint8_t registerValue = (opcodeWord & REGISTER_MASK);
    const uint8_t modeValue = (opcodeWord & MODE_MASK) >> 3U; //NOLINT

    const auto addressingMode = getAddressingMode(modeValue, registerValue);
    if(!addressingMode) {
        return std::unexpected(addressingMode.error());
    }

    GetAddressingModeDataParams getAddressingModeParams {
        .opSize = instructionData.size,
        .addressingMode = addressingMode.value(),
        .registerValue = registerValue,
        .addressingModeDataStartAddr = static_cast<uint32_t>(instructionStartAddr + sizeof(opcodeWord) + 2)
    };

    const auto addressingModeData = getAddressingModeData(*bus_, getAddressingModeParams);
    if(!addressingModeData) {
        return std::unexpected(addressingModeData.error());
    }

    const auto convertedAddressingModeData = convertAddressingModeData<InstructionData::MOVEM_InstructionData::AddressingModeData>(addressingModeData->data);
    if(!convertedAddressingModeData) {
        return std::unexpected(DecodeError::INVALID_ADDRESSING_MODE);
    }

    instructionData.addressingModeData = *convertedAddressingModeData;

}

} // namespace m68k::decoders_