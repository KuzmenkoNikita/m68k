#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/MOVE_USP_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t DR_MASK = 0b1000U;
constexpr uint16_t REGISTER_MASK = 0b111U;

} //namespace


MOVE_USP_Decoder::MOVE_USP_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> MOVE_USP_Decoder::decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const
{
    InstructionData::MOVE_USP_InstructionData instructionData{};

    instructionData.regNumber = opcodeWord & REGISTER_MASK;

    instructionData.direction = ((opcodeWord & DR_MASK) != 0) ? InstructionData::MOVE_USP_InstructionData::Direction::USP_TO_ADDR :
                                                                InstructionData::MOVE_USP_InstructionData::Direction::ADDR_TO_USP;

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(sizeof(opcodeWord))
    };
}

} // namespace m68k::decoders_