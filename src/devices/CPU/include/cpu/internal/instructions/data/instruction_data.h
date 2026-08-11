#pragma once
#include <cpu/internal/instructions/data/ABCD_instruction_data.h>
#include <cpu/internal/instructions/data/ADDA_instruction_data.h>
#include <cpu/internal/instructions/data/ADDI_instruction_data.h>
#include <cpu/internal/instructions/data/ADDQ_instruction_data.h>
#include <cpu/internal/instructions/data/ADDX_instruction_data.h>
#include <cpu/internal/instructions/data/ADD_instruction_data.h>
#include <cpu/internal/instructions/data/ANDI_instruction_data.h>
#include <cpu/internal/instructions/data/ANDI_to_CCR_instruction_data.h>
#include <cpu/internal/instructions/data/ANDI_to_SR_instruction_data.h>
#include <cpu/internal/instructions/data/AND_instruction_data.h>
#include <cpu/internal/instructions/data/ASL_memory_instruction_data.h>
#include <cpu/internal/instructions/data/ASL_register_instruction_data.h>
#include <cpu/internal/instructions/data/ASR_memory_instruction_data.h>
#include <cpu/internal/instructions/data/ASR_register_instruction_data.h>
#include <cpu/internal/instructions/data/BCHG_immediate_instruction_data.h>
#include <cpu/internal/instructions/data/BCHG_register_instruction_data.h>
#include <cpu/internal/instructions/data/BCLR_immediate_instruction_data.h>
#include <cpu/internal/instructions/data/BCLR_register_instruction_data.h>
#include <cpu/internal/instructions/data/BRA_instruction_data.h>
#include <cpu/internal/instructions/data/BSET_immediate_instruction_data.h>
#include <cpu/internal/instructions/data/BSET_register_instruction_data.h>
#include <cpu/internal/instructions/data/BSR_instruction_data.h>
#include <cpu/internal/instructions/data/BTST_immediate_instruction_data.h>
#include <cpu/internal/instructions/data/BTST_register_instruction_data.h>
#include <cpu/internal/instructions/data/Bcc_instruction_data.h>
#include <cpu/internal/instructions/data/CHK_instruction_data.h>
#include <cpu/internal/instructions/data/CLR_instruction_data.h>
#include <cpu/internal/instructions/data/CMPA_instruction_data.h>
#include <cpu/internal/instructions/data/CMPI_instruction_data.h>
#include <cpu/internal/instructions/data/CMPM_instruction_data.h>
#include <cpu/internal/instructions/data/CMP_instruction_data.h>
#include <cpu/internal/instructions/data/DBcc_instruction_data.h>
#include <cpu/internal/instructions/data/DIVS_instruction_data.h>
#include <cpu/internal/instructions/data/DIVU_instruction_data.h>
#include <cpu/internal/instructions/data/EORI_instruction_data.h>
#include <cpu/internal/instructions/data/EORI_to_CCR_instruction_data.h>
#include <cpu/internal/instructions/data/EORI_to_SR_instruction_data.h>
#include <cpu/internal/instructions/data/EOR_instruction_data.h>
#include <cpu/internal/instructions/data/EXG_instruction_data.h>
#include <cpu/internal/instructions/data/EXT_instruction_data.h>
#include <cpu/internal/instructions/data/ILLEGAL_instruction_data.h>
#include <cpu/internal/instructions/data/JMP_instruction_data.h>
#include <cpu/internal/instructions/data/JSR_instruction_data.h>
#include <cpu/internal/instructions/data/LEA_instruction_data.h>
#include <cpu/internal/instructions/data/LINK_instruction_data.h>
#include <cpu/internal/instructions/data/LSL_memory_instruction_data.h>
#include <cpu/internal/instructions/data/LSL_register_instruction_data.h>
#include <cpu/internal/instructions/data/LSR_memory_instruction_data.h>
#include <cpu/internal/instructions/data/LSR_register_instruction_data.h>
#include <cpu/internal/instructions/data/MOVEA_instruction_data.h>
#include <cpu/internal/instructions/data/MOVEM_instruction_data.h>
#include <cpu/internal/instructions/data/MOVEP_instruction_data.h>
#include <cpu/internal/instructions/data/MOVEQ_instruction_data.h>
#include <cpu/internal/instructions/data/MOVE_USP_instruction_data.h>
#include <cpu/internal/instructions/data/MOVE_from_SR_instruction_data.h>
#include <cpu/internal/instructions/data/MOVE_instruction_data.h>
#include <cpu/internal/instructions/data/MOVE_to_CCR_instruction_data.h>
#include <cpu/internal/instructions/data/MOVE_to_SR_instruction_data.h>
#include <cpu/internal/instructions/data/MULS_instruction_data.h>
#include <cpu/internal/instructions/data/MULU_instruction_data.h>
#include <cpu/internal/instructions/data/NBCD_instruction_data.h>
#include <cpu/internal/instructions/data/NEGX_instruction_data.h>
#include <cpu/internal/instructions/data/NEG_instruction_data.h>
#include <cpu/internal/instructions/data/NOT_instruction_data.h>
#include <cpu/internal/instructions/data/ORI_instruction_data.h>
#include <cpu/internal/instructions/data/ORI_to_CCR_instruction_data.h>
#include <cpu/internal/instructions/data/ORI_to_SR_instruction_data.h>
#include <cpu/internal/instructions/data/OR_instruction_data.h>
#include <cpu/internal/instructions/data/PEA_instruction_data.h>
#include <cpu/internal/instructions/data/ROL_memory_instruction_data.h>
#include <cpu/internal/instructions/data/ROL_register_instruction_data.h>
#include <cpu/internal/instructions/data/ROR_memory_instruction_data.h>
#include <cpu/internal/instructions/data/ROR_register_instruction_data.h>
#include <cpu/internal/instructions/data/ROXL_memory_instruction_data.h>
#include <cpu/internal/instructions/data/ROXL_register_instruction_data.h>
#include <cpu/internal/instructions/data/ROXR_memory_instruction_data.h>
#include <cpu/internal/instructions/data/ROXR_register_instruction_data.h>
#include <cpu/internal/instructions/data/SBCD_instruction_data.h>
#include <cpu/internal/instructions/data/STOP_instruction_data.h>
#include <cpu/internal/instructions/data/SUBA_instruction_data.h>
#include <cpu/internal/instructions/data/SUBI_instruction_data.h>
#include <cpu/internal/instructions/data/SUBQ_instruction_data.h>
#include <cpu/internal/instructions/data/SUBX_instruction_data.h>
#include <cpu/internal/instructions/data/SUB_instruction_data.h>
#include <cpu/internal/instructions/data/SWAP_instruction_data.h>
#include <cpu/internal/instructions/data/Scc_instruction_data.h>
#include <cpu/internal/instructions/data/TAS_instruction_data.h>
#include <cpu/internal/instructions/data/TRAP_instruction_data.h>
#include <cpu/internal/instructions/data/TST_instruction_data.h>
#include <cpu/internal/instructions/data/UNLK_instruction_data.h>
#include <cpu/internal/instructions/data/RESET_instruction_data.h>
#include <cpu/internal/instructions/data/NOP_instruction_data.h>
#include <cpu/internal/instructions/data/RTE_instruction_data.h>
#include <cpu/internal/instructions/data/RTS_instruction_data.h>
#include <cpu/internal/instructions/data/TRAPV_instruction_data.h>
#include <cpu/internal/instructions/data/RTR_instruction_data.h>

namespace m68k::InstructionData {

using InstructionDataVariant = std::variant<ORI_to_CCR_InstructionData,
                                            ORI_to_SR_InstructionData,
                                            ORI_InstructionData,
                                            ANDI_to_CCR_InstructionData,
                                            ANDI_to_SR_InstructionData,
                                            ANDI_InstructionData,
                                            SUBI_InstructionData,
                                            ADDI_InstructionData,
                                            EORI_to_CCR_InstructionData,
                                            EORI_to_SR_InstructionData,
                                            EORI_InstructionData,
                                            CMPI_InstructionData,
                                            BTST_Immediate_InstructionData,
                                            BTST_Register_InstructionData,
                                            BCHG_Immediate_InstructionData,
                                            BCHG_Register_InstructionData,
                                            BCLR_Immediate_InstructionData,
                                            BCLR_Register_InstructionData,
                                            BSET_Immediate_InstructionData,
                                            BSET_Register_InstructionData,
                                            MOVEP_InstructionData,
                                            MOVEA_InstructionData,
                                            MOVE_InstructionData,
                                            MOVE_from_SR_InstructionData,
                                            MOVE_to_CCR_InstructionData,
                                            MOVE_to_SR_InstructionData,
                                            NEGX_InstructionData,
                                            CLR_InstructionData,
                                            NEG_InstructionData,
                                            NOT_InstructionData,
                                            EXT_InstructionData,
                                            NBCD_InstructionData,
                                            SWAP_InstructionData,
                                            PEA_InstructionData,
                                            TAS_InstructionData,
                                            TST_InstructionData,
                                            TRAP_InstructionData,
                                            LINK_InstructionData,
                                            UNLK_InstructionData,
                                            MOVE_USP_InstructionData,
                                            STOP_InstructionData,
                                            JSR_InstructionData,
                                            JMP_InstructionData,
                                            MOVEM_InstructionData,
                                            LEA_InstructionData,
                                            CHK_InstructionData,
                                            ADDQ_InstructionData,
                                            SUBQ_InstructionData,
                                            Scc_InstructionData,
                                            DBcc_InstructionData,
                                            BRA_InstructionData,
                                            BSR_InstructionData,
                                            Bcc_InstructionData,
                                            MOVEQ_InstructionData,
                                            DIVU_InstructionData,
                                            DIVS_InstructionData,
                                            SBCD_InstructionData,
                                            OR_InstructionData,
                                            SUB_InstructionData,
                                            SUBX_InstructionData,
                                            SUBA_InstructionData,
                                            EOR_InstructionData,
                                            CMPM_InstructionData,
                                            CMP_InstructionData,
                                            CMPA_InstructionData,
                                            MULU_InstructionData,
                                            MULS_InstructionData,
                                            ABCD_InstructionData,
                                            EXG_InstructionData,
                                            AND_InstructionData,
                                            ADD_InstructionData,
                                            ADDX_InstructionData,
                                            ADDA_InstructionData,
                                            ASL_Memory_InstructionData,
                                            ASL_Register_InstructionData,
                                            ASR_Memory_InstructionData,
                                            ASR_Register_InstructionData,
                                            LSL_Memory_InstructionData,
                                            LSL_Register_InstructionData,
                                            LSR_Memory_InstructionData,
                                            LSR_Register_InstructionData,
                                            ROXL_Register_InstructionData,
                                            ROXL_Memory_InstructionData,
                                            ROXR_Register_InstructionData,
                                            ROXR_Memory_InstructionData,
                                            ROL_Memory_InstructionData,
                                            ROL_Register_InstructionData,
                                            ROR_Memory_InstructionData,
                                            ROR_Register_InstructionData,
                                            ILLEGAL_InstructionData,
                                            RESET_InstructionData,
                                            NOP_InstructionData,
                                            RTE_InstructionData,
                                            RTS_InstructionData,
                                            TRAPV_InstructionData,
                                            RTR_InstructionData>;

} //namespace m68k::InstructionData

