#pragma once
#include <cpu/internal/instruction_decoder/decode_result.h>
#include <cpu/internal/instruction_decoder/decoders/base_decoder.h>
#include <cpu/internal/instruction_decoder/instruction_decode_error.h>
#include <cpu/internal/instruction_decoder/instruction_type_decoder.h>
#include <cpu/internal/instructions/instruction.h>
#include <cstdint>
#include <expected>
#include <memory>
#include <memoryinterface.h>
#include <vector>
#include <optional>

namespace m68k {

class InstructionDecoder {
public:
    explicit InstructionDecoder(std::shared_ptr<DataExchange::MemoryInterface> bus);
    [[nodiscard]] std::expected<DecodeResult, DecodeError> decode(uint32_t pc); //NOLINT(*-identifier-length)

private:
    void initDecoders();
private:
    std::shared_ptr<DataExchange::MemoryInterface> bus_;
    std::unique_ptr<InstructionTypeDecoder> typeDecoder_;

    /// Временный optional, когда все декодеры будут реализованы, он будет убран
    std::vector<std::optional<std::unique_ptr<decoders_::IDecoder>>> decoders_;
};

} // namespace m68k