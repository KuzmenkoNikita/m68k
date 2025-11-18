#include <cpu/internal/instructions/instruction_factory.h>

namespace m68k {

Instruction InstructionsFactory::makeTST(InstructionData::TSTInstructionData data)
{
    return {InstructionType::TST, std::move(data)};
}

} //namespace m68k