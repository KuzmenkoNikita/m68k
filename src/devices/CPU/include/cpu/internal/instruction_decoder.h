#pragma once
#include <cpu/internal/instruction_params.h>
#include <cstdint>
#include <expected>
#include <memory>
#include <memoryinterface.h>
#include <array>
#include <cpu/internal/opcodes_masks.h>

namespace m68k {

class InstructionDecoder {
public:

    enum class DecodeError : uint8_t {
        INVALID_INSTRUCTION,
        MEMORY_READ_FAILURE
    };

    explicit InstructionDecoder(std::shared_ptr<DataExchange::MemoryInterface> bus);

    [[nodiscard]] std::expected<Instruction, DecodeError> decode(uint32_t pc); //NOLINT(*-identifier-length)

private:

    struct OpcodeIndo {
        uint16_t mask;
        uint16_t pattern;
        InstructionType type;
    };

private:
    std::shared_ptr<DataExchange::MemoryInterface> bus_;

    //NOLINTBEGIN
    std::array<OpcodeIndo, 96> opcodeTable_ = {
        OpcodeIndo{OPCODE_MASK_ORI_TO_CCR, OPCODE_PATTERN_ORI_to_CCR, InstructionType::ORI_to_CCR},
        OpcodeIndo{OPCODE_MASK_ORI_TO_SR, OPCODE_PATTERN_ORI_to_SR, InstructionType::ORI_to_SR},
        OpcodeIndo{OPCODE_MASK_ORI, OPCODE_PATTERN_ORI, InstructionType::ORI},
        OpcodeIndo{OPCODE_MASK_ANDI_TO_CCR, OPCODE_PATTERN_ANDI_to_CCR, InstructionType::ANDI_to_CCR},
        OpcodeIndo{OPCODE_MASK_ANDI_TO_SR, OPCODE_PATTERN_ANDI_to_SR, InstructionType::ANDI_to_SR},
        OpcodeIndo{OPCODE_MASK_ANDI, OPCODE_PATTERN_ANDI, InstructionType::ANDI},
        OpcodeIndo{OPCODE_MASK_SUBI, OPCODE_PATTERN_SUBI, InstructionType::SUBI},
        OpcodeIndo{OPCODE_MASK_ADDI, OPCODE_PATTERN_ADDI, InstructionType::ADDI},
        OpcodeIndo{OPCODE_MASK_EORI_TO_CCR, OPCODE_PATTERN_EORI_to_CCR, InstructionType::EORI_to_CCR},
        OpcodeIndo{OPCODE_MASK_EORI_TO_SR, OPCODE_PATTERN_EORI_to_SR, InstructionType::EORI_to_SR},
        OpcodeIndo{OPCODE_MASK_EORI, OPCODE_PATTERN_EORI, InstructionType::EORI},
        OpcodeIndo{OPCODE_MASK_CMPI, OPCODE_PATTERN_CMPI, InstructionType::CMPI},
        OpcodeIndo{OPCODE_MASK_BTST_DATA, OPCODE_PATTERN_BTST_DATA, InstructionType::BTST},
        OpcodeIndo{OPCODE_MASK_BCHG_DATA, OPCODE_PATTERN_BCHG_DATA, InstructionType::BCHG},
        OpcodeIndo{OPCODE_MASK_BCLR_DATA, OPCODE_PATTERN_BCLR_DATA, InstructionType::BCLR},
        OpcodeIndo{OPCODE_MASK_BSET_DATA, OPCODE_PATTERN_BSET_DATA, InstructionType::BSET},
        OpcodeIndo{OPCODE_MASK_BTST_REG, OPCODE_PATTERN_BTST_REG, InstructionType::BTST},
        OpcodeIndo{OPCODE_MASK_BCHG_REG, OPCODE_PATTERN_BCHG_REG, InstructionType::BCHG},
        OpcodeIndo{OPCODE_MASK_BCLR_REG, OPCODE_PATTERN_BCLR_REG, InstructionType::BCLR},
        OpcodeIndo{OPCODE_MASK_BSET_REG, OPCODE_PATTERN_BSET_REG, InstructionType::BSET},
        OpcodeIndo{OPCODE_MASK_MOVEP, OPCODE_PATTERN_MOVEP, InstructionType::MOVEP},
        OpcodeIndo{OPCODE_MASK_MOVEA, OPCODE_PATTERN_MOVEA, InstructionType::MOVEA},
        OpcodeIndo{OPCODE_MASK_MOVE, OPCODE_PATTERN_MOVE, InstructionType::MOVE},
        OpcodeIndo{OPCODE_MASK_MOVE_from_SR, OPCODE_PATTERN_MOVE_from_SR, InstructionType::MOVE_from_SR},
        OpcodeIndo{OPCODE_MASK_MOVE_to_CCR, OPCODE_PATTERN_MOVE_to_CCR, InstructionType::MOVE_to_CCR},
        OpcodeIndo{OPCODE_MASK_MOVE_to_SR, OPCODE_PATTERN_MOVE_to_SR, InstructionType::MOVE_to_SR},
        OpcodeIndo{OPCODE_MASK_NEGX, OPCODE_PATTERN_NEGX, InstructionType::NEGX},
        OpcodeIndo{OPCODE_MASK_CLR, OPCODE_PATTERN_CLR, InstructionType::CLR},
        OpcodeIndo{OPCODE_MASK_NEG, OPCODE_PATTERN_NEG, InstructionType::NEG},
        OpcodeIndo{OPCODE_MASK_NOT, OPCODE_PATTERN_NOT, InstructionType::NOT},
        OpcodeIndo{OPCODE_MASK_EXT, OPCODE_PATTERN_EXT, InstructionType::EXT},
        OpcodeIndo{OPCODE_MASK_NBCD, OPCODE_PATTERN_NBCD, InstructionType::NBCD},
        OpcodeIndo{OPCODE_MASK_SWAP, OPCODE_PATTERN_SWAP, InstructionType::SWAP},
        OpcodeIndo{OPCODE_MASK_PEA, OPCODE_PATTERN_PEA, InstructionType::PEA},
        OpcodeIndo{OPCODE_MASK_ILLEGAL, OPCODE_PATTERN_ILLEGAL, InstructionType::ILLEGAL},
        OpcodeIndo{OPCODE_MASK_TAS, OPCODE_PATTERN_TAS, InstructionType::TAS},
        OpcodeIndo{OPCODE_MASK_TST, OPCODE_PATTERN_TST, InstructionType::TST},
        OpcodeIndo{OPCODE_MASK_TRAP, OPCODE_PATTERN_TRAP, InstructionType::TRAP},
        OpcodeIndo{OPCODE_MASK_LINK, OPCODE_PATTERN_LINK, InstructionType::LINK},
        OpcodeIndo{OPCODE_MASK_UNLK, OPCODE_PATTERN_UNLK, InstructionType::UNLK},
        OpcodeIndo{OPCODE_MASK_MOVE_USP, OPCODE_PATTERN_MOVE_USP, InstructionType::MOVE_USP},
        OpcodeIndo{OPCODE_MASK_RESET, OPCODE_PATTERN_RESET, InstructionType::RESET},
        OpcodeIndo{OPCODE_MASK_NOP, OPCODE_PATTERN_NOP, InstructionType::NOP},
        OpcodeIndo{OPCODE_MASK_STOP, OPCODE_PATTERN_STOP, InstructionType::STOP},
        OpcodeIndo{OPCODE_MASK_RTE, OPCODE_PATTERN_RTE, InstructionType::RTE},
        OpcodeIndo{OPCODE_MASK_RTS, OPCODE_PATTERN_RTS, InstructionType::RTS},
        OpcodeIndo{OPCODE_MASK_TRAPV, OPCODE_PATTERN_TRAPV, InstructionType::TRAPV},
        OpcodeIndo{OPCODE_MASK_RTR, OPCODE_PATTERN_RTR, InstructionType::RTR},
        OpcodeIndo{OPCODE_MASK_JSR, OPCODE_PATTERN_JSR, InstructionType::JSR},
        OpcodeIndo{OPCODE_MASK_JMP, OPCODE_PATTERN_JMP, InstructionType::JMP},
        OpcodeIndo{OPCODE_MASK_MOVEM, OPCODE_PATTERN_MOVEM, InstructionType::MOVEM},
        OpcodeIndo{OPCODE_MASK_LEA, OPCODE_PATTERN_LEA, InstructionType::LEA},
        OpcodeIndo{OPCODE_MASK_CHK, OPCODE_PATTERN_CHK, InstructionType::CHK},
        OpcodeIndo{OPCODE_MASK_ADDQ, OPCODE_PATTERN_ADDQ, InstructionType::ADDQ},
        OpcodeIndo{OPCODE_MASK_SUBQ, OPCODE_PATTERN_SUBQ, InstructionType::SUBQ},
        OpcodeIndo{OPCODE_MASK_Scc, OPCODE_PATTERN_Scc, InstructionType::Scc},
        OpcodeIndo{OPCODE_MASK_DBcc, OPCODE_PATTERN_DBcc, InstructionType::DBcc},
        OpcodeIndo{OPCODE_MASK_BRA, OPCODE_PATTERN_BRA, InstructionType::BRA},
        OpcodeIndo{OPCODE_MASK_BSR, OPCODE_PATTERN_BSR, InstructionType::BSR},
        OpcodeIndo{OPCODE_MASK_Bcc, OPCODE_PATTERN_Bcc, InstructionType::Bcc},
        OpcodeIndo{OPCODE_MASK_MOVEQ, OPCODE_PATTERN_MOVEQ, InstructionType::MOVEQ},
        OpcodeIndo{OPCODE_MASK_DIVU, OPCODE_PATTERN_DIVU, InstructionType::DIVU},
        OpcodeIndo{OPCODE_MASK_DIVS, OPCODE_PATTERN_DIVS, InstructionType::DIVS},
        OpcodeIndo{OPCODE_MASK_SBCD, OPCODE_PATTERN_SBCD, InstructionType::SBCD},
        OpcodeIndo{OPCODE_MASK_OR, OPCODE_PATTERN_OR, InstructionType::OR},
        OpcodeIndo{OPCODE_MASK_SUB, OPCODE_PATTERN_SUB, InstructionType::SUB},
        OpcodeIndo{OPCODE_MASK_SUBX, OPCODE_PATTERN_SUBX, InstructionType::SUBX},
        OpcodeIndo{OPCODE_MASK_SUBA, OPCODE_PATTERN_SUBA, InstructionType::SUBA},
        OpcodeIndo{OPCODE_MASK_EOR, OPCODE_PATTERN_EOR, InstructionType::EOR},
        OpcodeIndo{OPCODE_MASK_CMPM, OPCODE_PATTERN_CMPM, InstructionType::CMPM},
        OpcodeIndo{OPCODE_MASK_CMP, OPCODE_PATTERN_CMP, InstructionType::CMP},
        OpcodeIndo{OPCODE_MASK_CMPA, OPCODE_PATTERN_CMPA, InstructionType::CMPA},
        OpcodeIndo{OPCODE_MASK_MULU, OPCODE_PATTERN_MULU, InstructionType::MULU},
        OpcodeIndo{OPCODE_MASK_MULS, OPCODE_PATTERN_MULS, InstructionType::MULS},
        OpcodeIndo{OPCODE_MASK_ABCD, OPCODE_PATTERN_ABCD, InstructionType::ABCD},
        OpcodeIndo{OPCODE_MASK_EXG, OPCODE_PATTERN_EXG, InstructionType::EXG},
        OpcodeIndo{OPCODE_MASK_AND, OPCODE_PATTERN_AND, InstructionType::AND},
        OpcodeIndo{OPCODE_MASK_ADD, OPCODE_PATTERN_ADD, InstructionType::ADD},
        OpcodeIndo{OPCODE_MASK_ADDX, OPCODE_PATTERN_ADDX, InstructionType::ADDX},
        OpcodeIndo{OPCODE_MASK_ADDA, OPCODE_PATTERN_ADDA, InstructionType::ADDA},
        OpcodeIndo{OPCODE_MASK_ASL_MEMORY, OPCODE_PATTERN_ASL_MEMORY, InstructionType::ASL},
        OpcodeIndo{OPCODE_MASK_ASL_REG, OPCODE_PATTERN_ASL_REG, InstructionType::ASL},
        OpcodeIndo{OPCODE_MASK_ASR_MEMORY, OPCODE_PATTERN_ASR_MEMORY, InstructionType::ASR},
        OpcodeIndo{OPCODE_MASK_ASR_REG, OPCODE_PATTERN_ASR_REG, InstructionType::ASR},
        OpcodeIndo{OPCODE_MASK_LSL_MEMORY, OPCODE_PATTERN_LSL_MEMORY, InstructionType::LSL},
        OpcodeIndo{OPCODE_MASK_LSL_REG, OPCODE_PATTERN_LSL_REG, InstructionType::LSL},
        OpcodeIndo{OPCODE_MASK_LSR_MEMORY, OPCODE_PATTERN_LSR_MEMORY, InstructionType::LSR},
        OpcodeIndo{OPCODE_MASK_LSR_REG, OPCODE_PATTERN_LSR_REG, InstructionType::LSR},
        OpcodeIndo{OPCODE_MASK_ROXL_MEMORY, OPCODE_PATTERN_ROXL_MEMORY, InstructionType::ROXL},
        OpcodeIndo{OPCODE_MASK_ROXL_REG, OPCODE_PATTERN_ROXL_REG, InstructionType::ROXL},
        OpcodeIndo{OPCODE_MASK_ROXR_MEMORY, OPCODE_PATTERN_ROXR_MEMORY, InstructionType::ROXR},
        OpcodeIndo{OPCODE_MASK_ROXR_REG, OPCODE_PATTERN_ROXR_REG, InstructionType::ROXR},
        OpcodeIndo{OPCODE_MASK_ROL_MEMORY, OPCODE_PATTERN_ROL_MEMORY, InstructionType::ROL},
        OpcodeIndo{OPCODE_MASK_ROL_REG, OPCODE_PATTERN_ROL_REG, InstructionType::ROL},
        OpcodeIndo{OPCODE_MASK_ROR_MEMORY, OPCODE_PATTERN_ROR_MEMORY, InstructionType::ROR},
        OpcodeIndo{OPCODE_MASK_ROR_REG, OPCODE_PATTERN_ROR_REG, InstructionType::ROR},
    };
    //NOLINTEND
};

} // namespace m68k