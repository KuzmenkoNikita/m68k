#pragma once
#include "base_decoder.h"

namespace m68k::decoders_ {

class TSTDecoder final : public BaseDecoder<TSTDecoder>
{
public:
    explicit TSTDecoder(std::shared_ptr<DataExchange::MemoryInterface> bus);

    [[nodiscard]] std::expected<DecodeResult, DecodeError> decodeImpl(uint16_t opcodeWord, uint32_t instructionStartAddr) const;
};

} // namespace m68k::decoders_ 