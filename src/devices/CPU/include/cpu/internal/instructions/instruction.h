#pragma once
#include <cpu/internal/instructions/data/instruction_data.h>
#include <cpu/internal/instructions/instruction_params.h>

namespace m68k {

class Instruction 
{
public:

    template <typename DataType>
    const DataType& data() const 
    {
        if constexpr (std::is_same_v<DataType, InstructionData::TST_InstructionData>) {
            return std::get<DataType>(data_);
        }
    }

    [[nodiscard]] InstructionType type() const
    {
        return type_;
    }

    //NOLINTBEGIN (*-explicit-constructor)
    Instruction(const InstructionData::ABCD_InstructionData& data);
    Instruction(const InstructionData::ADD_InstructionData& data);
    Instruction(const InstructionData::ADDA_InstructionData& data);
    Instruction(const InstructionData::ADDI_InstructionData& data);
    Instruction(const InstructionData::ADDQ_InstructionData& data);
    Instruction(const InstructionData::ADDX_InstructionData& data);
    Instruction(const InstructionData::AND_InstructionData& data);
    Instruction(const InstructionData::ANDI_InstructionData& data);
    Instruction(const InstructionData::ANDI_to_CCR_InstructionData& data);
    Instruction(const InstructionData::ANDI_to_SR_InstructionData& data);
    Instruction(const InstructionData::ASL_Memory_InstructionData& data);
    Instruction(const InstructionData::ASL_Register_InstructionData& data);
    Instruction(const InstructionData::ASR_Memory_InstructionData& data);
    Instruction(const InstructionData::ASR_Register_InstructionData& data);
    Instruction(const InstructionData::Bcc_InstructionData& data);
    Instruction(const InstructionData::BCHG_InstructionData& data);
    Instruction(const InstructionData::BCLR_InstructionData& data);
    Instruction(const InstructionData::BRA_InstructionData& data);
    Instruction(const InstructionData::BSET_InstructionData& data);
    Instruction(const InstructionData::BSR_InstructionData& data);
    Instruction(const InstructionData::BTST_InstructionData& data);
    Instruction(const InstructionData::CHK_InstructionData& data);
    Instruction(const InstructionData::CLR_InstructionData& data);
    Instruction(const InstructionData::CMP_InstructionData& data);
    Instruction(const InstructionData::CMPA_InstructionData& data);
    Instruction(const InstructionData::CMPI_InstructionData& data);
    Instruction(const InstructionData::CMPM_InstructionData& data);
    Instruction(const InstructionData::DBcc_InstructionData& data);
    Instruction(const InstructionData::DIVS_InstructionData& data);
    Instruction(const InstructionData::DIVU_InstructionData& data);
    Instruction(const InstructionData::EOR_InstructionData& data);
    Instruction(const InstructionData::EORI_InstructionData& data);
    Instruction(const InstructionData::EORI_to_CCR_InstructionData& data);
    Instruction(const InstructionData::EORI_to_SR_InstructionData& data);
    Instruction(const InstructionData::EXG_InstructionData& data);
    Instruction(const InstructionData::EXT_InstructionData& data);
    Instruction(const InstructionData::JMP_InstructionData& data);
    Instruction(const InstructionData::JSR_InstructionData& data);
    Instruction(const InstructionData::LEA_InstructionData& data);
    Instruction(const InstructionData::LINK_InstructionData& data);
    Instruction(const InstructionData::LSd_InstructionData& data);
    Instruction(const InstructionData::MOVE_from_SR_InstructionData& data);
    Instruction(const InstructionData::MOVE_InstructionData& data);
    Instruction(const InstructionData::MOVE_to_CCR_InstructionData& data);
    Instruction(const InstructionData::MOVE_to_SR_InstructionData& data);
    Instruction(const InstructionData::MOVE_USP_InstructionData& data);
    Instruction(const InstructionData::MOVEA_InstructionData& data);
    Instruction(const InstructionData::MOVEM_InstructionData& data);
    Instruction(const InstructionData::MOVEP_InstructionData& data);
    Instruction(const InstructionData::MOVEQ_InstructionData& data);
    Instruction(const InstructionData::MULS_InstructionData& data);
    Instruction(const InstructionData::MULU_InstructionData& data);
    Instruction(const InstructionData::NBCD_InstructionData& data);
    Instruction(const InstructionData::NEG_InstructionData& data);
    Instruction(const InstructionData::NEGX_InstructionData& data);
    Instruction(const InstructionData::NOT_InstructionData& data);
    Instruction(const InstructionData::OR_InstructionData& data);
    Instruction(const InstructionData::ORI_InstructionData& data);
    Instruction(const InstructionData::ORI_to_CCR_InstructionData& data);
    Instruction(const InstructionData::ORI_to_SR_InstructionData& data);
    Instruction(const InstructionData::PEA_InstructionData& data);
    Instruction(const InstructionData::ROd_InstructionData& data);
    Instruction(const InstructionData::ROXd_InstructionData& data);
    Instruction(const InstructionData::SBCD_InstructionData& data);
    Instruction(const InstructionData::Scc_InstructionData& data);
    Instruction(const InstructionData::STOP_InstructionData& data);
    Instruction(const InstructionData::SUB_InstructionData& data);
    Instruction(const InstructionData::SUBA_InstructionData& data);
    Instruction(const InstructionData::SUBI_InstructionData& data);
    Instruction(const InstructionData::SUBQ_InstructionData& data);
    Instruction(const InstructionData::SUBX_InstructionData& data);
    Instruction(const InstructionData::SWAP_InstructionData& data);
    Instruction(const InstructionData::TAS_InstructionData& data);
    Instruction(const InstructionData::TRAP_InstructionData& data);
    Instruction(const InstructionData::TST_InstructionData& data);
    Instruction(const InstructionData::UNLK_InstructionData& data);
    //NOLINTEND

private:
    InstructionType type_;
    InstructionData::InstructionDataVariant data_;

};

} //namespace m68k