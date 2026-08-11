#include "instructions/data/ILLEGAL_instruction_data.h"
#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_decoder/decoders/ILLEGAL_decoder.h>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {



ILLEGAL_Decoder::ILLEGAL_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus))
{

}

std::expected<DecodeResult, DecodeError> ILLEGAL_Decoder::decode(uint16_t opcodeWord, uint32_t /*instructionStartAddr*/) const
{

    InstructionData::ILLEGAL_InstructionData instructionData{};

    return DecodeResult {
        .instruction = instructionData,
        .instructionSizeBytes = static_cast<uint32_t>(sizeof(opcodeWord))
    };

}

} // namespace m68k::decoders_