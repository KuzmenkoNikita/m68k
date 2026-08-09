#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/ROXR_register_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t REGISTER_MASK = 0b111U;
constexpr uint16_t IR_MASK = 0b10'0000U;
constexpr uint16_t SIZE_MASK = 0b1100'0000U;
constexpr uint16_t COUNT_OR_REGISTER_MASK = 0b1110'0000'0000U;

} //namespace

ROXR_Register_Decoder::ROXR_Register_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> ROXR_Register_Decoder::decode(uint16_t opcodeWord, uint32_t /*instructionStartAddr*/) const
{
    InstructionData::ROXR_Register_InstructionData instructionData{};

    instructionData.dataRegisterToBeRotated = (opcodeWord & REGISTER_MASK);
    instructionData.countOrRegister = (opcodeWord & COUNT_OR_REGISTER_MASK) >> 9U; //NOLINT
    instructionData.rotateMode = (opcodeWord & IR_MASK) != 0 ?  InstructionData::ROXR_Register_InstructionData::RotateMode::REGISTER : 
                                                                InstructionData::ROXR_Register_InstructionData::RotateMode::IMMEDIATE;
    const auto sizeValue = (opcodeWord & SIZE_MASK) >> 6U; //NOLINT

    switch(sizeValue) {
        case 0b00: instructionData.size = OperationSize::BYTE; break; 
        case 0b01: instructionData.size = OperationSize::WORD; break; 
        case 0b10: instructionData.size = OperationSize::LONG; break; 
        default: return std::unexpected(DecodeError::INVALID_INSTRUCTION_SIZE);
    }

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(sizeof(opcodeWord))
    };
}

} // namespace m68k::decoders_