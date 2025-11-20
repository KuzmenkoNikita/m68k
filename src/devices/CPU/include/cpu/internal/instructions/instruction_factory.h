#pragma once
#include "instruction.h"
#include "instructions/data/ORI_to_CCR_instruction_data.h"

 namespace m68k {

class InstructionsFactory {

public:

    static Instruction makeTST(const InstructionData::TSTInstructionData& data);
    static Instruction makeORItoCCR(const InstructionData::ORI_to_CCR_InstructionData& data);

};

} // namespace m68k