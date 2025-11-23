#pragma once
#include <cpu/internal/instruction_decoder/decoders/base_decoder.h>
#include <memory>
#include <memoryinterface.h>
namespace m68k::decoders_ {

class TSTDecoder final : public IDecoder
{
public:
    explicit TSTDecoder(std::shared_ptr<DataExchange::MemoryInterface> bus);
    ~TSTDecoder() override = default;
    [[nodiscard]] std::expected<DecodeResult, DecodeError> decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const override;
private:
    std::shared_ptr<DataExchange::MemoryInterface> bus_;
};

} // namespace m68k::decoders_ 