#include <cpu/internal/instructions/instruction_factory.h>

namespace m68k {

Instruction InstructionsFactory::makeTST(const InstructionData::TSTInstructionData& data)
{
    return {InstructionType::TST, data};
}

Instruction InstructionsFactory::makeORItoCCR(const InstructionData::ORI_to_CCR_InstructionData& data)
{
    return {InstructionType::ORI_to_CCR, data};
}

} //namespace m68k