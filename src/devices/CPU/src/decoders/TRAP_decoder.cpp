#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/TRAP_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {

constexpr uint16_t VECTOR_MASK = 0b1111U;

} //namespace

TRAP_Decoder::TRAP_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> TRAP_Decoder::decode(uint16_t opcodeWord, uint32_t /*instructionStartAddr*/) const
{
    InstructionData::TRAP_InstructionData instructionData{};

    instructionData.vectorNumber = (opcodeWord & VECTOR_MASK);

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(sizeof(opcodeWord))
    };
}

} // namespace m68k::decoders_