#pragma once
#include <cpu/internal/instructions/data/ADDI_instruction_data.h>
#include <cpu/internal/instructions/data/ANDI_instruction_data.h>
#include <cpu/internal/instructions/data/ANDI_to_CCR_instruction_data.h>
#include <cpu/internal/instructions/data/ANDI_to_SR_instruction_data.h>
#include <cpu/internal/instructions/data/ORI_instruction_data.h>
#include <cpu/internal/instructions/data/ORI_to_CCR_instruction_data.h>
#include <cpu/internal/instructions/data/ORI_to_SR_instruction_data.h>
#include <cpu/internal/instructions/data/SUBI_instruction_data.h>
#include <cpu/internal/instructions/data/TST_instruction_data.h>
#include <cpu/internal/instructions/data/EORI_to_CCR_instruction_data.h>
#include <cpu/internal/instructions/data/EORI_to_SR_instruction_data.h>

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
                                            TSTInstructionData>;

} //namespace m68k::InstructionData

