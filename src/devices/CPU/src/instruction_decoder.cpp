#include <bus_helper/bus_helper.h>
#include <instruction_decoder/instruction_decoder.h>
#include <instructions/instruction_params.h>
#include <memory>

#include <instruction_decoder/decoders/ORI_to_CCR_decoder.h>
#include <instruction_decoder/decoders/ORI_to_SR_decoder.h>
#include <instruction_decoder/decoders/ORI_decoder.h>
#include <instruction_decoder/decoders/ANDI_to_CCR_decoder.h>
#include <instruction_decoder/decoders/ANDI_to_SR_decoder.h>
#include <instruction_decoder/decoders/ANDI_decoder.h>
#include <instruction_decoder/decoders/SUBI_decoder.h>
#include <instruction_decoder/decoders/ADDI_decoder.h>
#include <instruction_decoder/decoders/EORI_to_CCR_decoder.h>
#include <instruction_decoder/decoders/EORI_to_SR_decoder.h>
#include <instruction_decoder/decoders/EORI_decoder.h>
#include <instruction_decoder/decoders/CMPI_decoder.h>
#include <instruction_decoder/decoders/BTST_immediate_decoder.h>
#include <instruction_decoder/decoders/BTST_register_decoder.h>
#include <instruction_decoder/decoders/BCHG_immediate_decoder.h>
#include <instruction_decoder/decoders/BCHG_register_decoder.h>
#include <instruction_decoder/decoders/BCLR_immediate_decoder.h>
#include <instruction_decoder/decoders/BCLR_register_decoder.h>
#include <instruction_decoder/decoders/BSET_immediate_decoder.h>
#include <instruction_decoder/decoders/BSET_register_decoder.h>
#include <instruction_decoder/decoders/MOVEP_decoder.h>
#include <instruction_decoder/decoders/MOVEA_decoder.h>
#include <instruction_decoder/decoders/MOVE_decoder.h>
#include <instruction_decoder/decoders/MOVE_from_SR_decoder.h>
#include <instruction_decoder/decoders/MOVE_to_CCR_decoder.h>
#include <instruction_decoder/decoders/MOVE_to_SR_decoder.h>
#include <instruction_decoder/decoders/NEGX_decoder.h>
#include <instruction_decoder/decoders/CLR_decoder.h>
#include <instruction_decoder/decoders/NEG_decoder.h>
#include <instruction_decoder/decoders/NOT_decoder.h>
#include <instruction_decoder/decoders/EXT_decoder.h>
#include <instruction_decoder/decoders/NBCD_decoder.h>
#include <instruction_decoder/decoders/SWAP_decoder.h>
#include <instruction_decoder/decoders/PEA_decoder.h>
#include <instruction_decoder/decoders/ILLEGAL_decoder.h>
#include <instruction_decoder/decoders/TAS_decoder.h>
#include <instruction_decoder/decoders/TST_decoder.h>
#include <instruction_decoder/decoders/TRAP_decoder.h>
#include <instruction_decoder/decoders/LINK_decoder.h>
#include <instruction_decoder/decoders/UNLK_decoder.h>
#include <instruction_decoder/decoders/MOVE_USP_decoder.h>
#include <instruction_decoder/decoders/RESET_decoder.h>
#include <instruction_decoder/decoders/NOP_decoder.h>
#include <instruction_decoder/decoders/STOP_decoder.h>
#include <instruction_decoder/decoders/RTE_decoder.h>
#include <instruction_decoder/decoders/RTS_decoder.h>
#include <instruction_decoder/decoders/TRAPV_decoder.h>
#include <instruction_decoder/decoders/RTR_decoder.h>
#include <instruction_decoder/decoders/JSR_decoder.h>
#include <instruction_decoder/decoders/JMP_decoder.h>
#include <instruction_decoder/decoders/MOVEM_decoder.h>
#include <instruction_decoder/decoders/LEA_decoder.h>
#include <instruction_decoder/decoders/CHK_decoder.h>
#include <instruction_decoder/decoders/ADDQ_decoder.h>
#include <instruction_decoder/decoders/SUBQ_decoder.h>
#include <instruction_decoder/decoders/Scc_decoder.h>
#include <instruction_decoder/decoders/DBcc_decoder.h>
#include <instruction_decoder/decoders/BRA_decoder.h>
#include <instruction_decoder/decoders/BSR_decoder.h>
#include <instruction_decoder/decoders/Bcc_decoder.h>
#include <instruction_decoder/decoders/MOVEQ_decoder.h>
#include <instruction_decoder/decoders/DIVU_decoder.h>
#include <instruction_decoder/decoders/DIVS_decoder.h>
#include <instruction_decoder/decoders/SBCD_decoder.h>
#include <instruction_decoder/decoders/OR_decoder.h>
#include <instruction_decoder/decoders/SUB_decoder.h>
#include <instruction_decoder/decoders/SUBX_decoder.h>
#include <instruction_decoder/decoders/SUBA_decoder.h>
#include <instruction_decoder/decoders/EOR_decoder.h>
#include <instruction_decoder/decoders/CMPM_decoder.h>
#include <instruction_decoder/decoders/CMP_decoder.h>
#include <instruction_decoder/decoders/CMPA_decoder.h>
#include <instruction_decoder/decoders/MULU_decoder.h>
#include <instruction_decoder/decoders/MULS_decoder.h>
#include <instruction_decoder/decoders/ABCD_decoder.h>
#include <instruction_decoder/decoders/EXG_decoder.h>
#include <instruction_decoder/decoders/AND_decoder.h>
#include <instruction_decoder/decoders/ADD_decoder.h>
#include <instruction_decoder/decoders/ADDX_decoder.h>
#include <instruction_decoder/decoders/ADDA_decoder.h>
#include <instruction_decoder/decoders/ASL_memory_decoder.h>
#include <instruction_decoder/decoders/ASL_register_decoder.h>
#include <instruction_decoder/decoders/ASR_memory_decoder.h>
#include <instruction_decoder/decoders/ASR_register_decoder.h>
#include <instruction_decoder/decoders/LSL_memory_decoder.h>
#include <instruction_decoder/decoders/LSL_register_decoder.h>
#include <instruction_decoder/decoders/LSR_memory_decoder.h>
#include <instruction_decoder/decoders/LSR_register_decoder.h>
#include <instruction_decoder/decoders/ROXL_memory_decoder.h>
#include <instruction_decoder/decoders/ROXL_register_decoder.h>
#include <instruction_decoder/decoders/ROXR_memory_decoder.h>
#include <instruction_decoder/decoders/ROXR_register_decoder.h>
#include <instruction_decoder/decoders/ROL_memory_decoder.h>
#include <instruction_decoder/decoders/ROL_register_decoder.h>
#include <instruction_decoder/decoders/ROR_memory_decoder.h>
#include <instruction_decoder/decoders/ROR_register_decoder.h>

namespace m68k {

InstructionDecoder::InstructionDecoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : 
                                    bus_(std::move(bus))
                                    , typeDecoder_(std::make_unique<InstructionTypeDecoder>())
{
    initDecoders();
}

std::expected<DecodeResult, DecodeError> InstructionDecoder::decode(uint32_t pc) //NOLINT(*-identifier-length)
{
    const auto readResult = m68k::busHelper::read<uint16_t>(*bus_, pc);
    if(!readResult){
        return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
    }

    auto instructionTypeResult = typeDecoder_->decode(readResult->data);
    if(!instructionTypeResult) {
        return std::unexpected(DecodeError::INVALID_INSTRUCTION);
    }

    
    return decoders_.at(static_cast<size_t>(instructionTypeResult.value()))->decode(readResult.value().data, pc);
}

void InstructionDecoder::initDecoders()
{ 
    decoders_.reserve(static_cast<size_t>(InstructionType::INSTRUCTIONS_COUNT));

    decoders_[static_cast<size_t>(InstructionType::ORI_to_CCR)] = std::make_unique<decoders_::ORI_to_CCR_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ORI_to_SR)] = std::make_unique<decoders_::ORI_to_SR_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ORI)] = std::make_unique<decoders_::ORI_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ANDI_to_CCR)] = std::make_unique<decoders_::ANDI_to_CCR_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ANDI_to_SR)] = std::make_unique<decoders_::ANDI_to_SR_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ANDI)] = std::make_unique<decoders_::ANDI_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::SUBI)] = std::make_unique<decoders_::SUBI_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ADDI)] = std::make_unique<decoders_::ADDI_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::EORI_to_CCR)] = std::make_unique<decoders_::EORI_to_CCR_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::EORI_to_SR)] = std::make_unique<decoders_::EORI_to_SR_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::EORI)] = std::make_unique<decoders_::EORI_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::CMPI)] = std::make_unique<decoders_::CMPI_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::BTST_IMMEDIATE)] = std::make_unique<decoders_::BTST_Immediate_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::BTST_REGISTER)] = std::make_unique<decoders_::BTST_Register_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::BCHG_IMMEDIATE)] = std::make_unique<decoders_::BCHG_Immediate_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::BCHG_REGISTER)] = std::make_unique<decoders_::BCHG_Register_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::BCLR_IMMEDIATE)] = std::make_unique<decoders_::BCLR_Immediate_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::BCLR_REGISTER)] = std::make_unique<decoders_::BCLR_Register_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::BSET_IMMEDIATE)] = std::make_unique<decoders_::BSET_Immediate_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::BSET_REGISTER)] = std::make_unique<decoders_::BSET_Register_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::MOVEP)] = std::make_unique<decoders_::MOVEP_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::MOVEA)] = std::make_unique<decoders_::MOVEA_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::MOVE)] = std::make_unique<decoders_::MOVE_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::MOVE_from_SR)] = std::make_unique<decoders_::MOVE_from_SR_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::MOVE_to_CCR)] = std::make_unique<decoders_::MOVE_to_CCR_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::MOVE_to_SR)] = std::make_unique<decoders_::MOVE_to_SR_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::NEGX)] = std::make_unique<decoders_::NEGX_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::CLR)] = std::make_unique<decoders_::CLR_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::NEG)] = std::make_unique<decoders_::NEG_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::NOT)] = std::make_unique<decoders_::NOT_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::EXT)] = std::make_unique<decoders_::EXT_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::NBCD)] = std::make_unique<decoders_::NBCD_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::SWAP)] = std::make_unique<decoders_::SWAP_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::PEA)] = std::make_unique<decoders_::PEA_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ILLEGAL)] = std::make_unique<decoders_::ILLEGAL_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::TAS)] = std::make_unique<decoders_::TAS_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::TST)] = std::make_unique<decoders_::TST_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::TRAP)] = std::make_unique<decoders_::TRAP_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::LINK)] = std::make_unique<decoders_::LINK_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::UNLK)] = std::make_unique<decoders_::UNLK_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::MOVE_USP)] = std::make_unique<decoders_::MOVE_USP_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::RESET)] = std::make_unique<decoders_::RESET_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::NOP)] = std::make_unique<decoders_::NOP_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::STOP)] = std::make_unique<decoders_::STOP_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::RTE)] = std::make_unique<decoders_::RTE_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::RTS)] = std::make_unique<decoders_::RTS_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::TRAPV)] = std::make_unique<decoders_::TRAPV_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::RTR)] = std::make_unique<decoders_::RTR_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::JSR)] = std::make_unique<decoders_::JSR_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::JMP)] = std::make_unique<decoders_::JMP_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::MOVEM)] = std::make_unique<decoders_::MOVEM_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::LEA)] = std::make_unique<decoders_::LEA_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::CHK)] = std::make_unique<decoders_::CHK_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ADDQ)] = std::make_unique<decoders_::ADDQ_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::SUBQ)] = std::make_unique<decoders_::SUBQ_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::Scc)] = std::make_unique<decoders_::Scc_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::DBcc)] = std::make_unique<decoders_::DBcc_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::BRA)] = std::make_unique<decoders_::BRA_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::BSR)] = std::make_unique<decoders_::BSR_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::Bcc)] = std::make_unique<decoders_::Bcc_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::MOVEQ)] = std::make_unique<decoders_::MOVEQ_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::DIVU)] = std::make_unique<decoders_::DIVU_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::DIVS)] = std::make_unique<decoders_::DIVS_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::SBCD)] = std::make_unique<decoders_::SBCD_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::OR)] = std::make_unique<decoders_::OR_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::SUB)] = std::make_unique<decoders_::SUB_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::SUBX)] = std::make_unique<decoders_::SUBX_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::SUBA)] = std::make_unique<decoders_::SUBA_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::EOR)] = std::make_unique<decoders_::EOR_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::CMPM)] = std::make_unique<decoders_::CMPM_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::CMP)] = std::make_unique<decoders_::CMP_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::CMPA)] = std::make_unique<decoders_::CMPA_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::MULU)] = std::make_unique<decoders_::MULU_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::MULS)] = std::make_unique<decoders_::MULS_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ABCD)] = std::make_unique<decoders_::ABCD_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::EXG)] = std::make_unique<decoders_::EXG_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::AND)] = std::make_unique<decoders_::AND_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ADD)] = std::make_unique<decoders_::ADD_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ADDX)] = std::make_unique<decoders_::ADDX_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ADDA)] = std::make_unique<decoders_::ADDA_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ASL_MEMORY)] = std::make_unique<decoders_::ASL_Memory_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ASL_REG)] = std::make_unique<decoders_::ASL_Register_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ASR_MEMORY)] = std::make_unique<decoders_::ASR_Memory_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ASR_REG)] = std::make_unique<decoders_::ASR_Register_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::LSL_MEMORY)] = std::make_unique<decoders_::LSL_Memory_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::LSL_REG)] = std::make_unique<decoders_::LSL_Register_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::LSR_MEMORY)] = std::make_unique<decoders_::LSR_Memory_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::LSR_REG)] = std::make_unique<decoders_::LSR_Register_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ROXL_MEMORY)] = std::make_unique<decoders_::ROXL_Memory_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ROXL_REG)] = std::make_unique<decoders_::ROXL_Register_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ROXR_MEMORY)] = std::make_unique<decoders_::ROXR_Memory_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ROXR_REG)] = std::make_unique<decoders_::ROXR_Register_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ROL_MEMORY)] = std::make_unique<decoders_::ROL_Memory_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ROL_REG)] = std::make_unique<decoders_::ROL_Register_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ROR_MEMORY)] = std::make_unique<decoders_::ROR_Memory_Decoder>(bus_);
    decoders_[static_cast<size_t>(InstructionType::ROR_REG)] = std::make_unique<decoders_::ROR_Register_Decoder>(bus_);
}


} // namespace m68k