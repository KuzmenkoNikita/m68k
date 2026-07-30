#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/EXT_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t REGISTER_MASK = 0b111U;
constexpr uint16_t OPMODE_MASK = 0b1'1100'0000U;

} //namespace


EXT_Decoder::EXT_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> EXT_Decoder::decode(uint16_t opcodeWord, uint32_t /*instructionStartAddr*/) const
{
    InstructionData::EXT_InstructionData instructionData{};

    instructionData.dataRegisterNumber = (opcodeWord & REGISTER_MASK);

    const auto opcodeValue = (opcodeWord & REGISTER_MASK) >> 6U; //NOLINT

    switch(opcodeValue) {

        case 0b010: {
            instructionData.opMode = InstructionData::EXT_InstructionData::OpMode::BYTE_TO_WORD;
            break;
        }

        case 0b011: {
            instructionData.opMode = InstructionData::EXT_InstructionData::OpMode::WORD_TO_LONG;
            break;
        }

        case 0b111: {
            instructionData.opMode = InstructionData::EXT_InstructionData::OpMode::BYTE_TO_LONG;
            break;
        }

        default: return std::unexpected(DecodeError::INVALID_OPMODE);
    }


    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(sizeof(opcodeWord))
    };

}

} // namespace m68k::decoders_