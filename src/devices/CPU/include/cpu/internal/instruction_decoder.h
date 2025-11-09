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
        OpcodeIndo{OPCODE_MASK_ORI_TO_CCR, 0x003C, InstructionType::ORI_to_CCR},
        OpcodeIndo{OPCODE_MASK_ORI_TO_SR, 0x007C, InstructionType::ORI_to_SR},
        OpcodeIndo{OPCODE_MASK_ORI, 0x0000, InstructionType::ORI},
        OpcodeIndo{OPCODE_MASK_ANDI_TO_CCR, 0x023c, InstructionType::ANDI_to_CCR},
        OpcodeIndo{OPCODE_MASK_ANDI_TO_SR, 0x027C, InstructionType::ANDI_to_SR},
        OpcodeIndo{OPCODE_MASK_ANDI, 0x0200, InstructionType::ANDI},
        OpcodeIndo{OPCODE_MASK_SUBI, 0x0400, InstructionType::SUBI},
        OpcodeIndo{OPCODE_MASK_ADDI, 0x0600, InstructionType::ADDI},
        OpcodeIndo{OPCODE_MASK_EORI_TO_CCR, 0x0A3C, InstructionType::EORI_to_CCR},
        OpcodeIndo{OPCODE_MASK_EORI_TO_SR, 0x0A7C, InstructionType::EORI_to_SR},
        OpcodeIndo{OPCODE_MASK_EORI, 0x0A00, InstructionType::EORI},
        OpcodeIndo{OPCODE_MASK_CMPI, 0x0C00, InstructionType::CMPI},
        OpcodeIndo{OPCODE_MASK_BTST_DATA, 0x0800, InstructionType::BTST},
        OpcodeIndo{OPCODE_MASK_BCHG_DATA, 0x0840, InstructionType::BCHG},
        OpcodeIndo{OPCODE_MASK_BCLR_DATA, 0x0880, InstructionType::BCLR},
        OpcodeIndo{OPCODE_MASK_BSET_DATA, 0x08C0, InstructionType::BSET},
        OpcodeIndo{OPCODE_MASK_BTST_REG, 0x0100, InstructionType::BTST},
        OpcodeIndo{OPCODE_MASK_BCHG_REG, 0x0140, InstructionType::BCHG},
        OpcodeIndo{OPCODE_MASK_BCLR_REG, 0x0180, InstructionType::BCLR},
        OpcodeIndo{OPCODE_MASK_BSET_REG, 0x01C0, InstructionType::BSET},
        OpcodeIndo{OPCODE_MASK_MOVEP, 0x0108, InstructionType::MOVEP},
        OpcodeIndo{OPCODE_MASK_MOVEA, 0x0040, InstructionType::MOVEA},
        OpcodeIndo{OPCODE_MASK_MOVE, 0x0000, InstructionType::MOVE},
        OpcodeIndo{OPCODE_MASK_MOVE_from_SR, 0x40C0, InstructionType::MOVE_from_SR},
        OpcodeIndo{OPCODE_MASK_MOVE_to_CCR, 0x44C0, InstructionType::MOVE_to_CCR},
        OpcodeIndo{OPCODE_MASK_MOVE_to_SR, 0x46C0, InstructionType::MOVE_to_SR},
        OpcodeIndo{OPCODE_MASK_NEGX, 0x4000, InstructionType::NEGX},
        OpcodeIndo{OPCODE_MASK_CLR, 0x4200, InstructionType::CLR},
        OpcodeIndo{OPCODE_MASK_NEG, 0x4400, InstructionType::NEG},
        OpcodeIndo{OPCODE_MASK_NOT, 0x4600, InstructionType::NOT},
        OpcodeIndo{OPCODE_MASK_EXT, 0x4880, InstructionType::EXT},
        OpcodeIndo{OPCODE_MASK_NBCD, 0x4800, InstructionType::NBCD},
        OpcodeIndo{OPCODE_MASK_SWAP, 0x4840, InstructionType::SWAP},
        OpcodeIndo{OPCODE_MASK_PEA, 0x4840, InstructionType::PEA},
        OpcodeIndo{OPCODE_MASK_ILLEGAL, 0x4AFC, InstructionType::ILLEGAL},
        OpcodeIndo{OPCODE_MASK_TAS, 0x4AC0, InstructionType::TAS},
        OpcodeIndo{OPCODE_MASK_TST, 0x4A00, InstructionType::TST},
        OpcodeIndo{OPCODE_MASK_TRAP, 0x4E40, InstructionType::TRAP},
        OpcodeIndo{OPCODE_MASK_LINK, 0x4E50, InstructionType::LINK},
        OpcodeIndo{OPCODE_MASK_UNLK, 0x4E58, InstructionType::UNLK},
        OpcodeIndo{OPCODE_MASK_MOVE_USP, 0x4E60, InstructionType::MOVE_USP},
        OpcodeIndo{OPCODE_MASK_RESET, 0x4E70, InstructionType::RESET},
        OpcodeIndo{OPCODE_MASK_NOP, 0x4E71, InstructionType::NOP},
        OpcodeIndo{OPCODE_MASK_STOP, 0x4E72, InstructionType::STOP},
        OpcodeIndo{OPCODE_MASK_RTE, 0x4E73, InstructionType::RTE},
        OpcodeIndo{OPCODE_MASK_RTS, 0x4E75, InstructionType::RTS},
        OpcodeIndo{OPCODE_MASK_TRAPV, 0x4E76, InstructionType::TRAPV},
        OpcodeIndo{OPCODE_MASK_RTR, 0x4E77, InstructionType::RTR},
        OpcodeIndo{OPCODE_MASK_JSR, 0x4E80, InstructionType::JSR},
        OpcodeIndo{OPCODE_MASK_JMP, 0x4EC0, InstructionType::JMP},
        OpcodeIndo{OPCODE_MASK_MOVEM, 0x4880, InstructionType::MOVEM},
        OpcodeIndo{OPCODE_MASK_LEA, 0x41C0, InstructionType::LEA},
        OpcodeIndo{OPCODE_MASK_CHK, 0x4180, InstructionType::CHK},
        OpcodeIndo{OPCODE_MASK_ADDQ, 0x5000, InstructionType::ADDQ},
        OpcodeIndo{OPCODE_MASK_SUBQ, 0x5100, InstructionType::SUBQ},
        OpcodeIndo{OPCODE_MASK_Scc, 0x50C0, InstructionType::Scc},
        OpcodeIndo{OPCODE_MASK_DBcc, 0x50C8, InstructionType::DBcc},
        OpcodeIndo{OPCODE_MASK_BRA, 0x6000, InstructionType::BRA},
        OpcodeIndo{OPCODE_MASK_BSR, 0x6100, InstructionType::BSR},
        OpcodeIndo{OPCODE_MASK_Bcc, 0x6000, InstructionType::Bcc},
        OpcodeIndo{OPCODE_MASK_MOVEQ, 0x7000, InstructionType::MOVEQ},
        OpcodeIndo{OPCODE_MASK_DIVU, 0x80C0, InstructionType::DIVU},
        OpcodeIndo{OPCODE_MASK_DIVS, 0x81C0, InstructionType::DIVS},
        OpcodeIndo{OPCODE_MASK_SBCD, 0x8100, InstructionType::SBCD},
        OpcodeIndo{OPCODE_MASK_OR, 0x8000, InstructionType::OR},
        OpcodeIndo{OPCODE_MASK_SUB, 0x9000, InstructionType::SUB},
        OpcodeIndo{OPCODE_MASK_SUBX, 0x9100, InstructionType::SUBX},
        OpcodeIndo{OPCODE_MASK_SUBA, 0x90C0, InstructionType::SUBA},
        OpcodeIndo{OPCODE_MASK_EOR, 0xB100, InstructionType::EOR},
        OpcodeIndo{OPCODE_MASK_CMPM, 0xB108, InstructionType::CMPM},
        OpcodeIndo{OPCODE_MASK_CMP, 0xB000, InstructionType::CMP},
        OpcodeIndo{OPCODE_MASK_CMPA, 0xB0C0, InstructionType::CMPA},
        OpcodeIndo{OPCODE_MASK_MULU, 0xC0C0, InstructionType::MULU},
        OpcodeIndo{OPCODE_MASK_MULS, 0xC1C0, InstructionType::MULS},
        OpcodeIndo{OPCODE_MASK_ABCD, 0xC100, InstructionType::ABCD},
        OpcodeIndo{OPCODE_MASK_EXG, 0xC100, InstructionType::EXG},
        OpcodeIndo{OPCODE_MASK_AND, 0xC000, InstructionType::AND},
        OpcodeIndo{OPCODE_MASK_ADD, 0xD000, InstructionType::ADD},
        OpcodeIndo{OPCODE_MASK_ADDX, 0xD100, InstructionType::ADDX},
        OpcodeIndo{OPCODE_MASK_ADDA, 0xD0C0, InstructionType::ADDA},
        OpcodeIndo{OPCODE_MASK_ASL_MEMORY, 0xE1C0, InstructionType::ASL},
        OpcodeIndo{OPCODE_MASK_ASL_REG, 0xE100, InstructionType::ASL},
        OpcodeIndo{OPCODE_MASK_ASR_MEMORY, 0xE0C0, InstructionType::ASR},
        OpcodeIndo{OPCODE_MASK_ASR_REG, 0xE000, InstructionType::ASR},
        OpcodeIndo{OPCODE_MASK_LSL_MEMORY, 0xE3C0, InstructionType::LSL},
        OpcodeIndo{OPCODE_MASK_LSL_REG, 0xE108, InstructionType::LSL},
        OpcodeIndo{OPCODE_MASK_LSR_MEMORY, 0xE2C0, InstructionType::LSR},
        OpcodeIndo{OPCODE_MASK_LSR_REG, 0xE008, InstructionType::LSR},
        OpcodeIndo{OPCODE_MASK_ROXL_MEMORY, 0xE5C0, InstructionType::ROXL},
        OpcodeIndo{OPCODE_MASK_ROXL_REG, 0xE110, InstructionType::ROXL},
        OpcodeIndo{OPCODE_MASK_ROXR_MEMORY, 0xE4C0, InstructionType::ROXR},
        OpcodeIndo{OPCODE_MASK_ROXR_REG, 0xE010, InstructionType::ROXR},
        OpcodeIndo{OPCODE_MASK_ROL_MEMORY, 0xE7C0, InstructionType::ROL},
        OpcodeIndo{OPCODE_MASK_ROL_REG, 0xE118, InstructionType::ROL},
        OpcodeIndo{OPCODE_MASK_ROR_MEMORY, 0xE6C0, InstructionType::ROR},
        OpcodeIndo{OPCODE_MASK_ROR_REG, 0xE018, InstructionType::ROR},
    };
    //NOLINTEND
};

} // namespace m68k