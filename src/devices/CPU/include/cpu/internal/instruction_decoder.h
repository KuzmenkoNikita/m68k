#pragma once
#include <cpu/internal/instruction_params.h>
#include <cstdint>
#include <expected>
#include <memory>
#include <memoryinterface.h>
#include <array>

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
    std::array<OpcodeIndo, 80> opcodeTable_ = {
        OpcodeIndo{0xFFFF, 0x003C, InstructionType::ORI_to_CCR},
        OpcodeIndo{0xFFFF, 0x007C, InstructionType::ORI_to_SR},
        OpcodeIndo{0xF000, 0x0000, InstructionType::ORI},
        OpcodeIndo{0xFFFF, 0x023c, InstructionType::ANDI_to_CCR},
        OpcodeIndo{0xFFFF, 0x027C, InstructionType::ANDI_to_SR},
        OpcodeIndo{0xF000, 0x0200, InstructionType::ANDI},
        OpcodeIndo{0xF000, 0x0400, InstructionType::SUBI},
        OpcodeIndo{0xF000, 0x0600, InstructionType::ADDI},
        OpcodeIndo{0xFFFF, 0x0A3C, InstructionType::EORI_to_CCR},
        OpcodeIndo{0xFFFF, 0x0A7C, InstructionType::EORI_to_SR},
        OpcodeIndo{0xF000, 0x0A00, InstructionType::EORI},
        OpcodeIndo{0xF000, 0x0C00, InstructionType::CMPI},
        OpcodeIndo{0xFFC0, 0x0800, InstructionType::BTST},
        OpcodeIndo{0xFFC0, 0x0840, InstructionType::BCHG},
        OpcodeIndo{0xFFC0, 0x0880, InstructionType::BCLR},
        OpcodeIndo{0xFFC0, 0x08C0, InstructionType::BSET},
        OpcodeIndo{0xF1C0, 0x0100, InstructionType::BTST},
        OpcodeIndo{0xF1C0, 0x0140, InstructionType::BCHG},
        OpcodeIndo{0xF1C0, 0x0180, InstructionType::BCLR},
        OpcodeIndo{0xF1C0, 0x01C0, InstructionType::BSET},
        OpcodeIndo{0xF138, 0x0108, InstructionType::MOVEP},
        OpcodeIndo{0xC1C0, 0x0040, InstructionType::MOVEA},
        OpcodeIndo{0xC000, 0x0000, InstructionType::MOVE},
        OpcodeIndo{0xFFC0, 0x40C0, InstructionType::MOVE_from_SR},
        OpcodeIndo{0xFFC0, 0x44C0, InstructionType::MOVE_to_CCR},
        OpcodeIndo{0xFFC0, 0x46C0, InstructionType::MOVE_to_SR},
        OpcodeIndo{0xFF00, 0x4000, InstructionType::NEGX},
        OpcodeIndo{0xFF00, 0x4200, InstructionType::CLR},
        OpcodeIndo{0xFF00, 0x4400, InstructionType::NEG},
        OpcodeIndo{0xFF00, 0x4600, InstructionType::NOT},
        OpcodeIndo{0xFFB8, 0x4880, InstructionType::EXT},
        OpcodeIndo{0xFFC0, 0x4800, InstructionType::NBCD},
        OpcodeIndo{0xFFF8, 0x4840, InstructionType::SWAP},
        OpcodeIndo{0xFFC0, 0x4840, InstructionType::PEA},
        OpcodeIndo{0xFFFF, 0x4AFC, InstructionType::ILLEGAL},
        OpcodeIndo{0xFFC0, 0x4AC0, InstructionType::TAS},
        OpcodeIndo{0xFF00, 0x4A00, InstructionType::TST},
        OpcodeIndo{0xFFF0, 0x4E40, InstructionType::TRAP},
        OpcodeIndo{0xFFF8, 0x4E50, InstructionType::LINK},
        OpcodeIndo{0xFFF8, 0x4E58, InstructionType::UNLK},
        OpcodeIndo{0xFFF0, 0x4E60, InstructionType::MOVE_USP},
        OpcodeIndo{0xFFFF, 0x4E70, InstructionType::RESET},
        OpcodeIndo{0xFFFF, 0x4E71, InstructionType::NOP},
        OpcodeIndo{0xFFFF, 0x4E72, InstructionType::STOP},
        OpcodeIndo{0xFFFF, 0x4E73, InstructionType::RTE},
        OpcodeIndo{0xFFFF, 0x4E75, InstructionType::RTS},
        OpcodeIndo{0xFFFF, 0x4E76, InstructionType::TRAPV},
        OpcodeIndo{0xFFFF, 0x4E77, InstructionType::RTR},
        OpcodeIndo{0xFFC0, 0x4E80, InstructionType::JSR},
        OpcodeIndo{0xFFC0, 0x4EC0, InstructionType::JMP},
        OpcodeIndo{0xFB80, 0x4880, InstructionType::MOVEM},
        OpcodeIndo{0xF1C0, 0x41C0, InstructionType::LEA},
        OpcodeIndo{0xF1C0, 0x4180, InstructionType::CHK},
        OpcodeIndo{0xF100, 0x5000, InstructionType::ADDQ},
        OpcodeIndo{0xF100, 0x5100, InstructionType::SUBQ},
        OpcodeIndo{0xF0C0, 0x50C0, InstructionType::Scc},
        OpcodeIndo{0xF0F8, 0x50C8, InstructionType::DBcc},
        OpcodeIndo{0xFF00, 0x6000, InstructionType::BRA},
        OpcodeIndo{0xFF00, 0x6100, InstructionType::BSR},
        OpcodeIndo{0xF000, 0x6000, InstructionType::Bcc},
        OpcodeIndo{0xF100, 0x7000, InstructionType::MOVEQ},
        OpcodeIndo{0xF1C0, 0x80C0, InstructionType::DIVU},
        OpcodeIndo{0xF1C0, 0x81C0, InstructionType::DIVS},
        OpcodeIndo{0xF1F0, 0x8100, InstructionType::SBCD},
        OpcodeIndo{0xF000, 0x8000, InstructionType::OR},
        OpcodeIndo{0xF000, 0x9000, InstructionType::SUB},
        OpcodeIndo{0xF130, 0x9100, InstructionType::SUBX},
        OpcodeIndo{0xF0C0, 0x90C0, InstructionType::SUBA},
        OpcodeIndo{0xF100, 0xB100, InstructionType::EOR},
        OpcodeIndo{0xF138, 0xB108, InstructionType::CMPM},

    };
    //NOLINTEND
};

} // namespace m68k