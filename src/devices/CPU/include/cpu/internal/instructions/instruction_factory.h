#pragma once
#include "instruction.h"

 namespace m68k {

class InstructionsFactory {

public:

    static Instruction makeTST(InstructionData::TSTInstructionData data);

};

} // namespace m68k