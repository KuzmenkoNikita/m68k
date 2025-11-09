#pragma once
#include <cpu/internal/instruction_decode_error.h>
#include <cpu/internal/instruction_type_decoder.h>
#include <cstdint>
#include <expected>
#include <memory>
#include <memoryinterface.h>

namespace m68k {

class InstructionTypeDecoder;

class InstructionDecoder {
public:
    explicit InstructionDecoder(std::shared_ptr<DataExchange::MemoryInterface> bus);
    //[[nodiscard]] std::expected<Instruction, DecodeError> decode(uint32_t pc); //NOLINT(*-identifier-length)

private:
    std::shared_ptr<DataExchange::MemoryInterface> bus_;
    std::unique_ptr<InstructionTypeDecoder> typeDecoder_;
};

} // namespace m68k