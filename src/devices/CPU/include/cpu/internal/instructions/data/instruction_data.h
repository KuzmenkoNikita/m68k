#pragma once
#include <cpu/internal/instructions/data/ADDI_instruction_data.h>
#include <cpu/internal/instructions/data/ANDI_instruction_data.h>
#include <cpu/internal/instructions/data/ANDI_to_CCR_instruction_data.h>
#include <cpu/internal/instructions/data/ANDI_to_SR_instruction_data.h>
#include <cpu/internal/instructions/data/CMPI_instruction_data.h>
#include <cpu/internal/instructions/data/EORI_instruction_data.h>
#include <cpu/internal/instructions/data/EORI_to_CCR_instruction_data.h>
#include <cpu/internal/instructions/data/EORI_to_SR_instruction_data.h>
#include <cpu/internal/instructions/data/ORI_instruction_data.h>
#include <cpu/internal/instructions/data/ORI_to_CCR_instruction_data.h>
#include <cpu/internal/instructions/data/ORI_to_SR_instruction_data.h>
#include <cpu/internal/instructions/data/SUBI_instruction_data.h>
#include <cpu/internal/instructions/data/TST_instruction_data.h>
#include <cpu/internal/instructions/data/BTST_instruction_data.h>
#include <cpu/internal/instructions/data/BCHG_instruction_data.h>
#include <cpu/internal/instructions/data/BCLR_instruction_data.h>
#include <cpu/internal/instructions/data/BSET_instruction_data.h>
#include <cpu/internal/instructions/data/MOVEP_instruction_data.h>
#include <cpu/internal/instructions/data/MOVEA_instruction_data.h>
#include <cpu/internal/instructions/data/MOVE_instruction_data.h>
#include <cpu/internal/instructions/data/MOVE_from_SR_instruction_data.h>
#include <cpu/internal/instructions/data/MOVE_to_CCR_instruction_data.h>
#include <cpu/internal/instructions/data/MOVE_to_SR_instruction_data.h>
#include <cpu/internal/instructions/data/NEGX_instruction_data.h>
#include <cpu/internal/instructions/data/CLR_instruction_data.h>
#include <cpu/internal/instructions/data/NEG_instruction_data.h>
#include <cpu/internal/instructions/data/NOT_instruction_data.h>
#include <cpu/internal/instructions/data/EXT_instruction_data.h>
#include <cpu/internal/instructions/data/NBCD_instruction_data.h>
#include <cpu/internal/instructions/data/SWAP_instruction_data.h>
#include <cpu/internal/instructions/data/PEA_instruction_data.h>
#include <cpu/internal/instructions/data/TAS_instruction_data.h>
#include <cpu/internal/instructions/data/TRAP_instruction_data.h>
#include <cpu/internal/instructions/data/LINK_instruction_data.h>
#include <cpu/internal/instructions/data/UNLK_instruction_data.h>
#include <cpu/internal/instructions/data/MOVE_USP_instruction_data.h>

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
                                            BTST_InstructionData,
                                            BCHG_InstructionData,
                                            BCLR_InstructionData,
                                            BSET_InstructionData,
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
                                            MOVE_USP_InstructionData>;

} //namespace m68k::InstructionData

