#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/EXG_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t RY_MASK = 0b111U;
constexpr uint16_t RX_MASK = 0b1110'0000'0000U;
constexpr uint16_t OPMODE_MASK = 0b1111'1000U;

} //namespace


EXG_Decoder::EXG_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> EXG_Decoder::decode(uint16_t opcodeWord, uint32_t /*instructionStartAddr*/) const
{
    InstructionData::EXG_InstructionData instructionData{};

    instructionData.registerRx = (opcodeWord & RX_MASK) >> 9U; //NOLINT
    instructionData.registerRy = (opcodeWord & RY_MASK); //NOLINT

    const auto opmodeValue = (opcodeWord & OPMODE_MASK) >> 3U; //NOLINT

    switch(opmodeValue) {

        case 0b01000: {
            instructionData.exchangeType = InstructionData::EXG_InstructionData::ExchaneType::DATA_REG;
            break;
        }

        case 0b01001: {
            instructionData.exchangeType = InstructionData::EXG_InstructionData::ExchaneType::ADDRESS_REG;
            break;
        }

        case 0b10001: {
            instructionData.exchangeType = InstructionData::EXG_InstructionData::ExchaneType::DATA_REG_AND_ADDRESS_REG;
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