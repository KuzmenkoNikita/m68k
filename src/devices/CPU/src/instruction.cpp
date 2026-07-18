#include <cpu/internal/instructions/instruction.h>

namespace m68k {

Instruction::Instruction(const InstructionData::ABCD_InstructionData& data) : 
    type_(InstructionType::ABCD)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::ADD_InstructionData& data) :
    type_(InstructionType::ADD)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::ADDA_InstructionData& data) :
    type_(InstructionType::ADDA)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::ADDI_InstructionData& data) :
    type_(InstructionType::ADDI)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::ADDQ_InstructionData& data) :
    type_(InstructionType::ADDQ)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::ADDX_InstructionData& data) :
    type_(InstructionType::ADDX)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::AND_InstructionData& data) :
    type_(InstructionType::AND)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::ANDI_InstructionData& data) :
    type_(InstructionType::ANDI)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::ANDI_to_CCR_InstructionData& data) :
    type_(InstructionType::ANDI_to_CCR)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::ANDI_to_SR_InstructionData& data) :
    type_(InstructionType::ANDI_to_SR)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::ASd_InstructionData& data) :
    type_(InstructionType::ASd)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::Bcc_InstructionData& data) :
    type_(InstructionType::Bcc)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::BCHG_InstructionData& data) :
    type_(InstructionType::BCHG)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::BCLR_InstructionData& data) :
    type_(InstructionType::BCLR)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::BRA_InstructionData& data) :
    type_(InstructionType::BRA)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::BSET_InstructionData& data) :
    type_(InstructionType::BSET)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::BSR_InstructionData& data) :
    type_(InstructionType::BSR)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::BTST_InstructionData& data) :
    type_(InstructionType::BTST)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::CHK_InstructionData& data) :
    type_(InstructionType::CHK)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::CLR_InstructionData& data) :
    type_(InstructionType::CLR)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::CMP_InstructionData& data) :
    type_(InstructionType::CMP)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::CMPA_InstructionData& data) :
    type_(InstructionType::CMPA)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::CMPI_InstructionData& data) :
    type_(InstructionType::CMPI)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::CMPM_InstructionData& data) :
    type_(InstructionType::CMPM)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::DBcc_InstructionData& data) :
    type_(InstructionType::DBcc)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::DIVS_InstructionData& data) :
    type_(InstructionType::DIVS)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::DIVU_InstructionData& data) :
    type_(InstructionType::DIVU)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::EOR_InstructionData& data) :
    type_(InstructionType::EOR)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::EORI_InstructionData& data) :
    type_(InstructionType::EORI)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::EORI_to_CCR_InstructionData& data) :
    type_(InstructionType::EORI_to_CCR)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::EORI_to_SR_InstructionData& data) :
    type_(InstructionType::EORI_to_SR)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::EXG_InstructionData& data) :
    type_(InstructionType::EXG)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::EXT_InstructionData& data) :
    type_(InstructionType::EXT)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::JMP_InstructionData& data) :
    type_(InstructionType::JMP)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::JSR_InstructionData& data) :
    type_(InstructionType::JSR)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::LEA_InstructionData& data) :
    type_(InstructionType::LEA)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::LINK_InstructionData& data) :
    type_(InstructionType::LINK)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::LSd_InstructionData& data) :
    type_(InstructionType::LSd)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::MOVE_from_SR_InstructionData& data) :
    type_(InstructionType::MOVE_from_SR)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::MOVE_InstructionData& data) :
    type_(InstructionType::MOVE)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::MOVE_to_CCR_InstructionData& data) :
    type_(InstructionType::MOVE_to_CCR)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::MOVE_to_SR_InstructionData& data) :
    type_(InstructionType::MOVE_to_SR)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::MOVE_USP_InstructionData& data) :
    type_(InstructionType::MOVE_USP)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::MOVEA_InstructionData& data) :
    type_(InstructionType::MOVEA)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::MOVEM_InstructionData& data) :
    type_(InstructionType::MOVEM)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::MOVEP_InstructionData& data) :
    type_(InstructionType::MOVEP)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::MOVEQ_InstructionData& data) :
    type_(InstructionType::MOVEQ)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::MULS_InstructionData& data) :
    type_(InstructionType::MULS)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::MULU_InstructionData& data) :
    type_(InstructionType::MULU)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::NBCD_InstructionData& data) :
    type_(InstructionType::NBCD)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::NEG_InstructionData& data) :
    type_(InstructionType::NEG)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::NEGX_InstructionData& data) :
    type_(InstructionType::NEGX)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::NOT_InstructionData& data) :
    type_(InstructionType::NOT)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::OR_InstructionData& data) :
    type_(InstructionType::OR)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::ORI_InstructionData& data) :
    type_(InstructionType::ORI)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::ORI_to_CCR_InstructionData& data) : 
    type_(InstructionType::ORI_to_CCR)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::ORI_to_SR_InstructionData& data) :
    type_(InstructionType::ORI_to_SR)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::PEA_InstructionData& data) :
    type_(InstructionType::PEA)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::ROd_InstructionData& data) :
    type_(InstructionType::ROd)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::ROXd_InstructionData& data) :
    type_(InstructionType::ROXd)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::SBCD_InstructionData& data) :
    type_(InstructionType::SBCD)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::Scc_InstructionData& data) :
    type_(InstructionType::Scc)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::STOP_InstructionData& data) :
    type_(InstructionType::STOP)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::SUB_InstructionData& data) :
    type_(InstructionType::SUB)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::SUBA_InstructionData& data) :
    type_(InstructionType::SUBA)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::SUBI_InstructionData& data) :
    type_(InstructionType::SUBI)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::SUBQ_InstructionData& data) :
    type_(InstructionType::SUBQ)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::SUBX_InstructionData& data) :
    type_(InstructionType::SUBX)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::SWAP_InstructionData& data) :
    type_(InstructionType::SWAP)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::TAS_InstructionData& data) :
    type_(InstructionType::TAS)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::TRAP_InstructionData& data) :
    type_(InstructionType::TRAP)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::TST_InstructionData& data) : 
    type_(InstructionType::TST)
    , data_(data)
{

}







} //namespace m68k