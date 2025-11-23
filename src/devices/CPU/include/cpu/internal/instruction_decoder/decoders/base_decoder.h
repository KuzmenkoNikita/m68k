#pragma once
#include <cpu/internal/instruction_decoder/decode_result.h>
#include <cpu/internal/instruction_decoder/instruction_decode_error.h>
#include <expected>

namespace m68k::decoders_ {
class IDecoder {
public:

    virtual ~IDecoder() = default;

    [[nodiscard]] virtual std::expected<DecodeResult, DecodeError> decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const = 0;
};

} // namespace m68k::decoders_