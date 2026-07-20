#pragma once

#include <cpu/internal/instruction_decoder/decoders/base_decoder.h>
#include <memory>
#include <memoryinterface.h>

namespace m68k::decoders_ {

class ADDX_Decoder final : public IDecoder
{
public:
    explicit ADDX_Decoder(std::shared_ptr<DataExchange::MemoryInterface> bus);
    [[nodiscard]] std::expected<DecodeResult, DecodeError> decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const override;
private:
    std::shared_ptr<DataExchange::MemoryInterface> bus_;
};

} //namespace m68k::decoders_