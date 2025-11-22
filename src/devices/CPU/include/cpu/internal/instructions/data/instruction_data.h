#pragma once
#include <cpu/internal/instructions/data/ORI_to_CCR_instruction_data.h>
#include <cpu/internal/instructions/data/ORI_to_SR_instruction_data.h>
#include <cpu/internal/instructions/data/tst_instruction_data.h>

namespace m68k::InstructionData {

using InstructionDataVariant = std::variant<TSTInstructionData,
                                            ORI_to_CCR_InstructionData,
                                            ORI_to_SR_InstructionData>;

} //namespace m68k::InstructionData

