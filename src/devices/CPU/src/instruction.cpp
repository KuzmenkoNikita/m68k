#include <cpu/internal/instructions/instruction.h>

namespace m68k {

Instruction::Instruction(const InstructionData::TSTInstructionData& data) : 
    type_(InstructionType::TST)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::ORI_to_CCR_InstructionData& data) : 
    type_(InstructionType::ORI_to_CCR)
    , data_(data)
{

}

Instruction::Instruction(const InstructionData::ORI_to_SR_InstructionData& data) :
    type_(InstructionType::ORI_to_CCR)
    , data_(data)
{

}

} //namespace m68k