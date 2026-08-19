#pragma once
#include "instruction_decode_error.h"
#include "opcodes_masks.h"
#include <array>
#include <cpu/internal/instructions/instruction_params.h>
#include <expected>

namespace m68k {

class InstructionTypeDecoder
{
public:
    [[nodiscard]] std::expected<InstructionType, DecodeError> decode(uint16_t opcodeValue) const;
    
private:
    struct OpcodeInfo {
        uint16_t mask;
        uint16_t pattern;
        InstructionType type;
    };

private:
    static constexpr std::array<OpcodeInfo, 98> opcodeTable_ = { //NOLINT(*-magic-numbers)
        OpcodeInfo{.mask=OPCODE_MASK_ORI_TO_CCR, .pattern=OPCODE_PATTERN_ORI_to_CCR, .type=InstructionType::ORI_to_CCR},
        OpcodeInfo{.mask=OPCODE_MASK_ORI_TO_SR, .pattern=OPCODE_PATTERN_ORI_to_SR, .type=InstructionType::ORI_to_SR},
        OpcodeInfo{.mask=OPCODE_MASK_ORI, .pattern=OPCODE_PATTERN_ORI, .type=InstructionType::ORI},
        OpcodeInfo{.mask=OPCODE_MASK_ANDI_TO_CCR, .pattern=OPCODE_PATTERN_ANDI_to_CCR, .type=InstructionType::ANDI_to_CCR},
        OpcodeInfo{.mask=OPCODE_MASK_ANDI_TO_SR, .pattern=OPCODE_PATTERN_ANDI_to_SR, .type=InstructionType::ANDI_to_SR},
        OpcodeInfo{.mask=OPCODE_MASK_ANDI, .pattern=OPCODE_PATTERN_ANDI, .type=InstructionType::ANDI},
        OpcodeInfo{.mask=OPCODE_MASK_SUBI, .pattern=OPCODE_PATTERN_SUBI, .type=InstructionType::SUBI},
        OpcodeInfo{.mask=OPCODE_MASK_ADDI, .pattern=OPCODE_PATTERN_ADDI, .type=InstructionType::ADDI},
        OpcodeInfo{.mask=OPCODE_MASK_EORI_TO_CCR, .pattern=OPCODE_PATTERN_EORI_to_CCR, .type=InstructionType::EORI_to_CCR},
        OpcodeInfo{.mask=OPCODE_MASK_EORI_TO_SR, .pattern=OPCODE_PATTERN_EORI_to_SR, .type=InstructionType::EORI_to_SR},
        OpcodeInfo{.mask=OPCODE_MASK_EORI, .pattern=OPCODE_PATTERN_EORI, .type=InstructionType::EORI},
        OpcodeInfo{.mask=OPCODE_MASK_CMPI, .pattern=OPCODE_PATTERN_CMPI, .type=InstructionType::CMPI},
        OpcodeInfo{.mask=OPCODE_MASK_BTST_DATA, .pattern=OPCODE_PATTERN_BTST_DATA, .type=InstructionType::BTST_IMMEDIATE},
        OpcodeInfo{.mask=OPCODE_MASK_BTST_REG, .pattern=OPCODE_PATTERN_BTST_REG, .type=InstructionType::BTST_REGISTER},
        OpcodeInfo{.mask=OPCODE_MASK_BCHG_DATA, .pattern=OPCODE_PATTERN_BCHG_DATA, .type=InstructionType::BCHG_IMMEDIATE},
        OpcodeInfo{.mask=OPCODE_MASK_BCHG_REG, .pattern=OPCODE_PATTERN_BCHG_REG, .type=InstructionType::BCHG_REGISTER},
        OpcodeInfo{.mask=OPCODE_MASK_BCLR_DATA, .pattern=OPCODE_PATTERN_BCLR_DATA, .type=InstructionType::BCLR_IMMEDIATE},
        OpcodeInfo{.mask=OPCODE_MASK_BCLR_REG, .pattern=OPCODE_PATTERN_BCLR_REG, .type=InstructionType::BCLR_REGISTER},
        OpcodeInfo{.mask=OPCODE_MASK_BSET_DATA, .pattern=OPCODE_PATTERN_BSET_DATA, .type=InstructionType::BSET_IMMEDIATE},
        OpcodeInfo{.mask=OPCODE_MASK_BSET_REG, .pattern=OPCODE_PATTERN_BSET_REG, .type=InstructionType::BSET_REGISTER},
        OpcodeInfo{.mask=OPCODE_MASK_TST, .pattern=OPCODE_PATTERN_TST, .type=InstructionType::TST},
        OpcodeInfo{.mask=OPCODE_MASK_MOVEP, .pattern=OPCODE_PATTERN_MOVEP, .type=InstructionType::MOVEP},
        OpcodeInfo{.mask=OPCODE_MASK_MOVEA, .pattern=OPCODE_PATTERN_MOVEA, .type=InstructionType::MOVEA},
        OpcodeInfo{.mask=OPCODE_MASK_MOVE, .pattern=OPCODE_PATTERN_MOVE, .type=InstructionType::MOVE},
        OpcodeInfo{.mask=OPCODE_MASK_MOVE_from_SR, .pattern=OPCODE_PATTERN_MOVE_from_SR, .type=InstructionType::MOVE_from_SR},
        OpcodeInfo{.mask=OPCODE_MASK_MOVE_to_CCR, .pattern=OPCODE_PATTERN_MOVE_to_CCR, .type=InstructionType::MOVE_to_CCR},
        OpcodeInfo{.mask=OPCODE_MASK_MOVE_to_SR, .pattern=OPCODE_PATTERN_MOVE_to_SR, .type=InstructionType::MOVE_to_SR},
        OpcodeInfo{.mask=OPCODE_MASK_NEGX, .pattern=OPCODE_PATTERN_NEGX, .type=InstructionType::NEGX},
        OpcodeInfo{.mask=OPCODE_MASK_CLR, .pattern=OPCODE_PATTERN_CLR, .type=InstructionType::CLR},
        OpcodeInfo{.mask=OPCODE_MASK_NEG, .pattern=OPCODE_PATTERN_NEG, .type=InstructionType::NEG},
        OpcodeInfo{.mask=OPCODE_MASK_NOT, .pattern=OPCODE_PATTERN_NOT, .type=InstructionType::NOT},
        OpcodeInfo{.mask=OPCODE_MASK_EXT, .pattern=OPCODE_PATTERN_EXT, .type=InstructionType::EXT},
        OpcodeInfo{.mask=OPCODE_MASK_NBCD, .pattern=OPCODE_PATTERN_NBCD, .type=InstructionType::NBCD},
        OpcodeInfo{.mask=OPCODE_MASK_SWAP, .pattern=OPCODE_PATTERN_SWAP, .type=InstructionType::SWAP},
        OpcodeInfo{.mask=OPCODE_MASK_PEA, .pattern=OPCODE_PATTERN_PEA, .type=InstructionType::PEA},
        OpcodeInfo{.mask=OPCODE_MASK_ILLEGAL, .pattern=OPCODE_PATTERN_ILLEGAL, .type=InstructionType::ILLEGAL},
        OpcodeInfo{.mask=OPCODE_MASK_TAS, .pattern=OPCODE_PATTERN_TAS, .type=InstructionType::TAS},
        OpcodeInfo{.mask=OPCODE_MASK_TRAP, .pattern=OPCODE_PATTERN_TRAP, .type=InstructionType::TRAP},
        OpcodeInfo{.mask=OPCODE_MASK_LINK, .pattern=OPCODE_PATTERN_LINK, .type=InstructionType::LINK},
        OpcodeInfo{.mask=OPCODE_MASK_UNLK, .pattern=OPCODE_PATTERN_UNLK, .type=InstructionType::UNLK},
        OpcodeInfo{.mask=OPCODE_MASK_MOVE_USP, .pattern=OPCODE_PATTERN_MOVE_USP, .type=InstructionType::MOVE_USP},
        OpcodeInfo{.mask=OPCODE_MASK_RESET, .pattern=OPCODE_PATTERN_RESET, .type=InstructionType::RESET},
        OpcodeInfo{.mask=OPCODE_MASK_NOP, .pattern=OPCODE_PATTERN_NOP, .type=InstructionType::NOP},
        OpcodeInfo{.mask=OPCODE_MASK_STOP, .pattern=OPCODE_PATTERN_STOP, .type=InstructionType::STOP},
        OpcodeInfo{.mask=OPCODE_MASK_RTE, .pattern=OPCODE_PATTERN_RTE, .type=InstructionType::RTE},
        OpcodeInfo{.mask=OPCODE_MASK_RTS, .pattern=OPCODE_PATTERN_RTS, .type=InstructionType::RTS},
        OpcodeInfo{.mask=OPCODE_MASK_TRAPV, .pattern=OPCODE_PATTERN_TRAPV, .type=InstructionType::TRAPV},
        OpcodeInfo{.mask=OPCODE_MASK_RTR, .pattern=OPCODE_PATTERN_RTR, .type=InstructionType::RTR},
        OpcodeInfo{.mask=OPCODE_MASK_JSR, .pattern=OPCODE_PATTERN_JSR, .type=InstructionType::JSR},
        OpcodeInfo{.mask=OPCODE_MASK_JMP, .pattern=OPCODE_PATTERN_JMP, .type=InstructionType::JMP},
        OpcodeInfo{.mask=OPCODE_MASK_MOVEM, .pattern=OPCODE_PATTERN_MOVEM, .type=InstructionType::MOVEM},
        OpcodeInfo{.mask=OPCODE_MASK_LEA, .pattern=OPCODE_PATTERN_LEA, .type=InstructionType::LEA},
        OpcodeInfo{.mask=OPCODE_MASK_CHK, .pattern=OPCODE_PATTERN_CHK, .type=InstructionType::CHK},
        OpcodeInfo{.mask=OPCODE_MASK_ADDQ, .pattern=OPCODE_PATTERN_ADDQ, .type=InstructionType::ADDQ},
        OpcodeInfo{.mask=OPCODE_MASK_SUBQ, .pattern=OPCODE_PATTERN_SUBQ, .type=InstructionType::SUBQ},
        OpcodeInfo{.mask=OPCODE_MASK_Scc, .pattern=OPCODE_PATTERN_Scc, .type=InstructionType::Scc},
        OpcodeInfo{.mask=OPCODE_MASK_DBcc, .pattern=OPCODE_PATTERN_DBcc, .type=InstructionType::DBcc},
        OpcodeInfo{.mask=OPCODE_MASK_BRA, .pattern=OPCODE_PATTERN_BRA, .type=InstructionType::BRA},
        OpcodeInfo{.mask=OPCODE_MASK_BSR, .pattern=OPCODE_PATTERN_BSR, .type=InstructionType::BSR},
        OpcodeInfo{.mask=OPCODE_MASK_Bcc, .pattern=OPCODE_PATTERN_Bcc, .type=InstructionType::Bcc},
        OpcodeInfo{.mask=OPCODE_MASK_MOVEQ, .pattern=OPCODE_PATTERN_MOVEQ, .type=InstructionType::MOVEQ},
        OpcodeInfo{.mask=OPCODE_MASK_DIVU, .pattern=OPCODE_PATTERN_DIVU, .type=InstructionType::DIVU},
        OpcodeInfo{.mask=OPCODE_MASK_DIVS, .pattern=OPCODE_PATTERN_DIVS, .type=InstructionType::DIVS},
        OpcodeInfo{.mask=OPCODE_MASK_SBCD, .pattern=OPCODE_PATTERN_SBCD, .type=InstructionType::SBCD},
        OpcodeInfo{.mask=OPCODE_MASK_OR, .pattern=OPCODE_PATTERN_OR, .type=InstructionType::OR},
        OpcodeInfo{.mask=OPCODE_MASK_SUB, .pattern=OPCODE_PATTERN_SUB, .type=InstructionType::SUB},
        OpcodeInfo{.mask=OPCODE_MASK_SUBX, .pattern=OPCODE_PATTERN_SUBX, .type=InstructionType::SUBX},
        OpcodeInfo{.mask=OPCODE_MASK_SUBA, .pattern=OPCODE_PATTERN_SUBA, .type=InstructionType::SUBA},
        OpcodeInfo{.mask=OPCODE_MASK_EOR, .pattern=OPCODE_PATTERN_EOR, .type=InstructionType::EOR},
        OpcodeInfo{.mask=OPCODE_MASK_CMPM, .pattern=OPCODE_PATTERN_CMPM, .type=InstructionType::CMPM},
        OpcodeInfo{.mask=OPCODE_MASK_CMP, .pattern=OPCODE_PATTERN_CMP, .type=InstructionType::CMP},
        OpcodeInfo{.mask=OPCODE_MASK_CMPA, .pattern=OPCODE_PATTERN_CMPA, .type=InstructionType::CMPA},
        OpcodeInfo{.mask=OPCODE_MASK_MULU, .pattern=OPCODE_PATTERN_MULU, .type=InstructionType::MULU},
        OpcodeInfo{.mask=OPCODE_MASK_MULS, .pattern=OPCODE_PATTERN_MULS, .type=InstructionType::MULS},
        OpcodeInfo{.mask=OPCODE_MASK_ABCD, .pattern=OPCODE_PATTERN_ABCD, .type=InstructionType::ABCD},
        OpcodeInfo{.mask=OPCODE_MASK_EXG, .pattern=OPCODE_PATTERN_EXG_DR, .type=InstructionType::EXG},
        OpcodeInfo{.mask=OPCODE_MASK_EXG, .pattern=OPCODE_PATTERN_EXG_AR, .type=InstructionType::EXG},
        OpcodeInfo{.mask=OPCODE_MASK_EXG, .pattern=OPCODE_PATTERN_EXG_DR_AR, .type=InstructionType::EXG},
        OpcodeInfo{.mask=OPCODE_MASK_AND, .pattern=OPCODE_PATTERN_AND, .type=InstructionType::AND},
        OpcodeInfo{.mask=OPCODE_MASK_ADD, .pattern=OPCODE_PATTERN_ADD, .type=InstructionType::ADD},
        OpcodeInfo{.mask=OPCODE_MASK_ADDX, .pattern=OPCODE_PATTERN_ADDX, .type=InstructionType::ADDX},
        OpcodeInfo{.mask=OPCODE_MASK_ADDA, .pattern=OPCODE_PATTERN_ADDA, .type=InstructionType::ADDA},
        OpcodeInfo{.mask=OPCODE_MASK_ASL_MEMORY, .pattern=OPCODE_PATTERN_ASL_MEMORY, .type=InstructionType::ASL_MEMORY},
        OpcodeInfo{.mask=OPCODE_MASK_ASL_REG, .pattern=OPCODE_PATTERN_ASL_REG, .type=InstructionType::ASL_REG},
        OpcodeInfo{.mask=OPCODE_MASK_ASR_MEMORY, .pattern=OPCODE_PATTERN_ASR_MEMORY, .type=InstructionType::ASR_MEMORY},
        OpcodeInfo{.mask=OPCODE_MASK_ASR_REG, .pattern=OPCODE_PATTERN_ASR_REG, .type=InstructionType::ASR_REG},
        OpcodeInfo{.mask=OPCODE_MASK_LSL_MEMORY, .pattern=OPCODE_PATTERN_LSL_MEMORY, .type=InstructionType::LSL_MEMORY},
        OpcodeInfo{.mask=OPCODE_MASK_LSL_REG, .pattern=OPCODE_PATTERN_LSL_REG, .type=InstructionType::LSL_REG},
        OpcodeInfo{.mask=OPCODE_MASK_LSR_MEMORY, .pattern=OPCODE_PATTERN_LSR_MEMORY, .type=InstructionType::LSR_MEMORY},
        OpcodeInfo{.mask=OPCODE_MASK_LSR_REG, .pattern=OPCODE_PATTERN_LSR_REG, .type=InstructionType::LSR_REG},
        OpcodeInfo{.mask=OPCODE_MASK_ROXL_MEMORY, .pattern=OPCODE_PATTERN_ROXL_MEMORY, .type=InstructionType::ROXL_MEMORY},
        OpcodeInfo{.mask=OPCODE_MASK_ROXL_REG, .pattern=OPCODE_PATTERN_ROXL_REG, .type=InstructionType::ROXL_REG},
        OpcodeInfo{.mask=OPCODE_MASK_ROXR_MEMORY, .pattern=OPCODE_PATTERN_ROXR_MEMORY, .type=InstructionType::ROXR_MEMORY},
        OpcodeInfo{.mask=OPCODE_MASK_ROXR_REG, .pattern=OPCODE_PATTERN_ROXR_REG, .type=InstructionType::ROXR_REG},
        OpcodeInfo{.mask=OPCODE_MASK_ROL_MEMORY, .pattern=OPCODE_PATTERN_ROL_MEMORY, .type=InstructionType::ROL_MEMORY},
        OpcodeInfo{.mask=OPCODE_MASK_ROL_REG, .pattern=OPCODE_PATTERN_ROL_REG, .type=InstructionType::ROL_REG},
        OpcodeInfo{.mask=OPCODE_MASK_ROR_MEMORY, .pattern=OPCODE_PATTERN_ROR_MEMORY, .type=InstructionType::ROR_MEMORY},
        OpcodeInfo{.mask=OPCODE_MASK_ROR_REG, .pattern=OPCODE_PATTERN_ROR_REG, .type=InstructionType::ROR_REG},
    };
};

} // namespace m68k