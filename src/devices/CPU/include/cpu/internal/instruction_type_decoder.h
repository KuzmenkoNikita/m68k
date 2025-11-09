#pragma once
#include <array>
#include <cpu/internal/instruction_decode_error.h>
#include <cpu/internal/instruction_params.h>
#include <cpu/internal/opcodes_masks.h>
#include <expected>

namespace m68k {

class InstructionTypeDecoder
{
public:
    std::expected<InstructionType, DecodeError> decode(uint16_t opcodeValue);
    
private:
    struct OpcodeIndo {
        uint16_t mask;
        uint16_t pattern;
        InstructionType type;
    };

private:
    std::array<OpcodeIndo, 96> opcodeTable_ = { //NOLINT(*-magic-numbers)
        OpcodeIndo{.mask=OPCODE_MASK_ORI_TO_CCR, .pattern=OPCODE_PATTERN_ORI_to_CCR, .type=InstructionType::ORI_to_CCR},
        OpcodeIndo{.mask=OPCODE_MASK_ORI_TO_SR, .pattern=OPCODE_PATTERN_ORI_to_SR, .type=InstructionType::ORI_to_SR},
        OpcodeIndo{.mask=OPCODE_MASK_ORI, .pattern=OPCODE_PATTERN_ORI, .type=InstructionType::ORI},
        OpcodeIndo{.mask=OPCODE_MASK_ANDI_TO_CCR, .pattern=OPCODE_PATTERN_ANDI_to_CCR, .type=InstructionType::ANDI_to_CCR},
        OpcodeIndo{.mask=OPCODE_MASK_ANDI_TO_SR, .pattern=OPCODE_PATTERN_ANDI_to_SR, .type=InstructionType::ANDI_to_SR},
        OpcodeIndo{.mask=OPCODE_MASK_ANDI, .pattern=OPCODE_PATTERN_ANDI, .type=InstructionType::ANDI},
        OpcodeIndo{.mask=OPCODE_MASK_SUBI, .pattern=OPCODE_PATTERN_SUBI, .type=InstructionType::SUBI},
        OpcodeIndo{.mask=OPCODE_MASK_ADDI, .pattern=OPCODE_PATTERN_ADDI, .type=InstructionType::ADDI},
        OpcodeIndo{.mask=OPCODE_MASK_EORI_TO_CCR, .pattern=OPCODE_PATTERN_EORI_to_CCR, .type=InstructionType::EORI_to_CCR},
        OpcodeIndo{.mask=OPCODE_MASK_EORI_TO_SR, .pattern=OPCODE_PATTERN_EORI_to_SR, .type=InstructionType::EORI_to_SR},
        OpcodeIndo{.mask=OPCODE_MASK_EORI, .pattern=OPCODE_PATTERN_EORI, .type=InstructionType::EORI},
        OpcodeIndo{.mask=OPCODE_MASK_CMPI, .pattern=OPCODE_PATTERN_CMPI, .type=InstructionType::CMPI},
        OpcodeIndo{.mask=OPCODE_MASK_BTST_DATA, .pattern=OPCODE_PATTERN_BTST_DATA, .type=InstructionType::BTST},
        OpcodeIndo{.mask=OPCODE_MASK_BCHG_DATA, .pattern=OPCODE_PATTERN_BCHG_DATA, .type=InstructionType::BCHG},
        OpcodeIndo{.mask=OPCODE_MASK_BCLR_DATA, .pattern=OPCODE_PATTERN_BCLR_DATA, .type=InstructionType::BCLR},
        OpcodeIndo{.mask=OPCODE_MASK_BSET_DATA, .pattern=OPCODE_PATTERN_BSET_DATA, .type=InstructionType::BSET},
        OpcodeIndo{.mask=OPCODE_MASK_BTST_REG, .pattern=OPCODE_PATTERN_BTST_REG, .type=InstructionType::BTST},
        OpcodeIndo{.mask=OPCODE_MASK_BCHG_REG, .pattern=OPCODE_PATTERN_BCHG_REG, .type=InstructionType::BCHG},
        OpcodeIndo{.mask=OPCODE_MASK_BCLR_REG, .pattern=OPCODE_PATTERN_BCLR_REG, .type=InstructionType::BCLR},
        OpcodeIndo{.mask=OPCODE_MASK_BSET_REG, .pattern=OPCODE_PATTERN_BSET_REG, .type=InstructionType::BSET},
        OpcodeIndo{.mask=OPCODE_MASK_MOVEP, .pattern=OPCODE_PATTERN_MOVEP, .type=InstructionType::MOVEP},
        OpcodeIndo{.mask=OPCODE_MASK_MOVEA, .pattern=OPCODE_PATTERN_MOVEA, .type=InstructionType::MOVEA},
        OpcodeIndo{.mask=OPCODE_MASK_MOVE, .pattern=OPCODE_PATTERN_MOVE, .type=InstructionType::MOVE},
        OpcodeIndo{.mask=OPCODE_MASK_MOVE_from_SR, .pattern=OPCODE_PATTERN_MOVE_from_SR, .type=InstructionType::MOVE_from_SR},
        OpcodeIndo{.mask=OPCODE_MASK_MOVE_to_CCR, .pattern=OPCODE_PATTERN_MOVE_to_CCR, .type=InstructionType::MOVE_to_CCR},
        OpcodeIndo{.mask=OPCODE_MASK_MOVE_to_SR, .pattern=OPCODE_PATTERN_MOVE_to_SR, .type=InstructionType::MOVE_to_SR},
        OpcodeIndo{.mask=OPCODE_MASK_NEGX, .pattern=OPCODE_PATTERN_NEGX, .type=InstructionType::NEGX},
        OpcodeIndo{.mask=OPCODE_MASK_CLR, .pattern=OPCODE_PATTERN_CLR, .type=InstructionType::CLR},
        OpcodeIndo{.mask=OPCODE_MASK_NEG, .pattern=OPCODE_PATTERN_NEG, .type=InstructionType::NEG},
        OpcodeIndo{.mask=OPCODE_MASK_NOT, .pattern=OPCODE_PATTERN_NOT, .type=InstructionType::NOT},
        OpcodeIndo{.mask=OPCODE_MASK_EXT, .pattern=OPCODE_PATTERN_EXT, .type=InstructionType::EXT},
        OpcodeIndo{.mask=OPCODE_MASK_NBCD, .pattern=OPCODE_PATTERN_NBCD, .type=InstructionType::NBCD},
        OpcodeIndo{.mask=OPCODE_MASK_SWAP, .pattern=OPCODE_PATTERN_SWAP, .type=InstructionType::SWAP},
        OpcodeIndo{.mask=OPCODE_MASK_PEA, .pattern=OPCODE_PATTERN_PEA, .type=InstructionType::PEA},
        OpcodeIndo{.mask=OPCODE_MASK_ILLEGAL, .pattern=OPCODE_PATTERN_ILLEGAL, .type=InstructionType::ILLEGAL},
        OpcodeIndo{.mask=OPCODE_MASK_TAS, .pattern=OPCODE_PATTERN_TAS, .type=InstructionType::TAS},
        OpcodeIndo{.mask=OPCODE_MASK_TST, .pattern=OPCODE_PATTERN_TST, .type=InstructionType::TST},
        OpcodeIndo{.mask=OPCODE_MASK_TRAP, .pattern=OPCODE_PATTERN_TRAP, .type=InstructionType::TRAP},
        OpcodeIndo{.mask=OPCODE_MASK_LINK, .pattern=OPCODE_PATTERN_LINK, .type=InstructionType::LINK},
        OpcodeIndo{.mask=OPCODE_MASK_UNLK, .pattern=OPCODE_PATTERN_UNLK, .type=InstructionType::UNLK},
        OpcodeIndo{.mask=OPCODE_MASK_MOVE_USP, .pattern=OPCODE_PATTERN_MOVE_USP, .type=InstructionType::MOVE_USP},
        OpcodeIndo{.mask=OPCODE_MASK_RESET, .pattern=OPCODE_PATTERN_RESET, .type=InstructionType::RESET},
        OpcodeIndo{.mask=OPCODE_MASK_NOP, .pattern=OPCODE_PATTERN_NOP, .type=InstructionType::NOP},
        OpcodeIndo{.mask=OPCODE_MASK_STOP, .pattern=OPCODE_PATTERN_STOP, .type=InstructionType::STOP},
        OpcodeIndo{.mask=OPCODE_MASK_RTE, .pattern=OPCODE_PATTERN_RTE, .type=InstructionType::RTE},
        OpcodeIndo{.mask=OPCODE_MASK_RTS, .pattern=OPCODE_PATTERN_RTS, .type=InstructionType::RTS},
        OpcodeIndo{.mask=OPCODE_MASK_TRAPV, .pattern=OPCODE_PATTERN_TRAPV, .type=InstructionType::TRAPV},
        OpcodeIndo{.mask=OPCODE_MASK_RTR, .pattern=OPCODE_PATTERN_RTR, .type=InstructionType::RTR},
        OpcodeIndo{.mask=OPCODE_MASK_JSR, .pattern=OPCODE_PATTERN_JSR, .type=InstructionType::JSR},
        OpcodeIndo{.mask=OPCODE_MASK_JMP, .pattern=OPCODE_PATTERN_JMP, .type=InstructionType::JMP},
        OpcodeIndo{.mask=OPCODE_MASK_MOVEM, .pattern=OPCODE_PATTERN_MOVEM, .type=InstructionType::MOVEM},
        OpcodeIndo{.mask=OPCODE_MASK_LEA, .pattern=OPCODE_PATTERN_LEA, .type=InstructionType::LEA},
        OpcodeIndo{.mask=OPCODE_MASK_CHK, .pattern=OPCODE_PATTERN_CHK, .type=InstructionType::CHK},
        OpcodeIndo{.mask=OPCODE_MASK_ADDQ, .pattern=OPCODE_PATTERN_ADDQ, .type=InstructionType::ADDQ},
        OpcodeIndo{.mask=OPCODE_MASK_SUBQ, .pattern=OPCODE_PATTERN_SUBQ, .type=InstructionType::SUBQ},
        OpcodeIndo{.mask=OPCODE_MASK_Scc, .pattern=OPCODE_PATTERN_Scc, .type=InstructionType::Scc},
        OpcodeIndo{.mask=OPCODE_MASK_DBcc, .pattern=OPCODE_PATTERN_DBcc, .type=InstructionType::DBcc},
        OpcodeIndo{.mask=OPCODE_MASK_BRA, .pattern=OPCODE_PATTERN_BRA, .type=InstructionType::BRA},
        OpcodeIndo{.mask=OPCODE_MASK_BSR, .pattern=OPCODE_PATTERN_BSR, .type=InstructionType::BSR},
        OpcodeIndo{.mask=OPCODE_MASK_Bcc, .pattern=OPCODE_PATTERN_Bcc, .type=InstructionType::Bcc},
        OpcodeIndo{.mask=OPCODE_MASK_MOVEQ, .pattern=OPCODE_PATTERN_MOVEQ, .type=InstructionType::MOVEQ},
        OpcodeIndo{.mask=OPCODE_MASK_DIVU, .pattern=OPCODE_PATTERN_DIVU, .type=InstructionType::DIVU},
        OpcodeIndo{.mask=OPCODE_MASK_DIVS, .pattern=OPCODE_PATTERN_DIVS, .type=InstructionType::DIVS},
        OpcodeIndo{.mask=OPCODE_MASK_SBCD, .pattern=OPCODE_PATTERN_SBCD, .type=InstructionType::SBCD},
        OpcodeIndo{.mask=OPCODE_MASK_OR, .pattern=OPCODE_PATTERN_OR, .type=InstructionType::OR},
        OpcodeIndo{.mask=OPCODE_MASK_SUB, .pattern=OPCODE_PATTERN_SUB, .type=InstructionType::SUB},
        OpcodeIndo{.mask=OPCODE_MASK_SUBX, .pattern=OPCODE_PATTERN_SUBX, .type=InstructionType::SUBX},
        OpcodeIndo{.mask=OPCODE_MASK_SUBA, .pattern=OPCODE_PATTERN_SUBA, .type=InstructionType::SUBA},
        OpcodeIndo{.mask=OPCODE_MASK_EOR, .pattern=OPCODE_PATTERN_EOR, .type=InstructionType::EOR},
        OpcodeIndo{.mask=OPCODE_MASK_CMPM, .pattern=OPCODE_PATTERN_CMPM, .type=InstructionType::CMPM},
        OpcodeIndo{.mask=OPCODE_MASK_CMP, .pattern=OPCODE_PATTERN_CMP, .type=InstructionType::CMP},
        OpcodeIndo{.mask=OPCODE_MASK_CMPA, .pattern=OPCODE_PATTERN_CMPA, .type=InstructionType::CMPA},
        OpcodeIndo{.mask=OPCODE_MASK_MULU, .pattern=OPCODE_PATTERN_MULU, .type=InstructionType::MULU},
        OpcodeIndo{.mask=OPCODE_MASK_MULS, .pattern=OPCODE_PATTERN_MULS, .type=InstructionType::MULS},
        OpcodeIndo{.mask=OPCODE_MASK_ABCD, .pattern=OPCODE_PATTERN_ABCD, .type=InstructionType::ABCD},
        OpcodeIndo{.mask=OPCODE_MASK_EXG, .pattern=OPCODE_PATTERN_EXG, .type=InstructionType::EXG},
        OpcodeIndo{.mask=OPCODE_MASK_AND, .pattern=OPCODE_PATTERN_AND, .type=InstructionType::AND},
        OpcodeIndo{.mask=OPCODE_MASK_ADD, .pattern=OPCODE_PATTERN_ADD, .type=InstructionType::ADD},
        OpcodeIndo{.mask=OPCODE_MASK_ADDX, .pattern=OPCODE_PATTERN_ADDX, .type=InstructionType::ADDX},
        OpcodeIndo{.mask=OPCODE_MASK_ADDA, .pattern=OPCODE_PATTERN_ADDA, .type=InstructionType::ADDA},
        OpcodeIndo{.mask=OPCODE_MASK_ASL_MEMORY, .pattern=OPCODE_PATTERN_ASL_MEMORY, .type=InstructionType::ASL},
        OpcodeIndo{.mask=OPCODE_MASK_ASL_REG, .pattern=OPCODE_PATTERN_ASL_REG, .type=InstructionType::ASL},
        OpcodeIndo{.mask=OPCODE_MASK_ASR_MEMORY, .pattern=OPCODE_PATTERN_ASR_MEMORY, .type=InstructionType::ASR},
        OpcodeIndo{.mask=OPCODE_MASK_ASR_REG, .pattern=OPCODE_PATTERN_ASR_REG, .type=InstructionType::ASR},
        OpcodeIndo{.mask=OPCODE_MASK_LSL_MEMORY, .pattern=OPCODE_PATTERN_LSL_MEMORY, .type=InstructionType::LSL},
        OpcodeIndo{.mask=OPCODE_MASK_LSL_REG, .pattern=OPCODE_PATTERN_LSL_REG, .type=InstructionType::LSL},
        OpcodeIndo{.mask=OPCODE_MASK_LSR_MEMORY, .pattern=OPCODE_PATTERN_LSR_MEMORY, .type=InstructionType::LSR},
        OpcodeIndo{.mask=OPCODE_MASK_LSR_REG, .pattern=OPCODE_PATTERN_LSR_REG, .type=InstructionType::LSR},
        OpcodeIndo{.mask=OPCODE_MASK_ROXL_MEMORY, .pattern=OPCODE_PATTERN_ROXL_MEMORY, .type=InstructionType::ROXL},
        OpcodeIndo{.mask=OPCODE_MASK_ROXL_REG, .pattern=OPCODE_PATTERN_ROXL_REG, .type=InstructionType::ROXL},
        OpcodeIndo{.mask=OPCODE_MASK_ROXR_MEMORY, .pattern=OPCODE_PATTERN_ROXR_MEMORY, .type=InstructionType::ROXR},
        OpcodeIndo{.mask=OPCODE_MASK_ROXR_REG, .pattern=OPCODE_PATTERN_ROXR_REG, .type=InstructionType::ROXR},
        OpcodeIndo{.mask=OPCODE_MASK_ROL_MEMORY, .pattern=OPCODE_PATTERN_ROL_MEMORY, .type=InstructionType::ROL},
        OpcodeIndo{.mask=OPCODE_MASK_ROL_REG, .pattern=OPCODE_PATTERN_ROL_REG, .type=InstructionType::ROL},
        OpcodeIndo{.mask=OPCODE_MASK_ROR_MEMORY, .pattern=OPCODE_PATTERN_ROR_MEMORY, .type=InstructionType::ROR},
        OpcodeIndo{.mask=OPCODE_MASK_ROR_REG, .pattern=OPCODE_PATTERN_ROR_REG, .type=InstructionType::ROR},
    };
};


} // namespace m68k