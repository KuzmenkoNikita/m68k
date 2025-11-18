#pragma once
#include "instruction_decode_error.h"
#include "instruction_type_decoder.h"
#include <cpu/internal/instructions/instruction.h>
#include <cstdint>
#include <expected>
#include <memory>
#include <memoryinterface.h>

namespace m68k {

class InstructionTypeDecoder;

class InstructionDecoder {
public:
    explicit InstructionDecoder(std::shared_ptr<DataExchange::MemoryInterface> bus);
    [[nodiscard]] std::expected<Instruction, DecodeError> decode(uint32_t pc); //NOLINT(*-identifier-length)


private:
    [[nodiscard]] std::expected<InstructionData::TSTInstructionData, DecodeError> decodeTST(uint16_t opcode, uint32_t instructionDataAddr);

private:
    std::shared_ptr<DataExchange::MemoryInterface> bus_;
    std::unique_ptr<InstructionTypeDecoder> typeDecoder_;
};

} // namespace m68k