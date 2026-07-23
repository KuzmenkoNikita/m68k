#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/ASR_register_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {
    
constexpr uint16_t COUNT_OR_REGISTER_MASK = 0x0E00U;
constexpr uint16_t SIZE_MASK = 0x00C0U;
constexpr uint16_t IR_MASK = 0x0020U;
constexpr uint16_t REGISTER_MASK = 0x0007U;

} //namespace

ASR_Register_Decoder::ASR_Register_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> ASR_Register_Decoder::decode(uint16_t opcodeWord, uint32_t /*instructionStartAddr*/) const
{
    InstructionData::ASR_Register_InstructionData instructionData{};

    instructionData.dataRegisterToBeShifted = (opcodeWord & REGISTER_MASK);
    instructionData.countOrRegister = (opcodeWord & COUNT_OR_REGISTER_MASK) >> 9U; //NOLINT

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

    instructionData.shiftMode = (opcodeWord & IR_MASK) == 0 ? 
                                InstructionData::ASR_Register_InstructionData::ShiftMode::IMMEDIATE : 
                                InstructionData::ASR_Register_InstructionData::ShiftMode::REGISTER;


    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(sizeof(opcodeWord))
    };
}


} // namespace m68k::decoders_