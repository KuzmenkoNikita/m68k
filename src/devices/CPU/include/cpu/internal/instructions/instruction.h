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
        if constexpr (std::is_same_v<DataType, InstructionData::TSTInstructionData>) {
            return std::get<DataType>();
        }
    }

    [[nodiscard]] InstructionType type() const
    {
        return type_;
    }

    //NOLINTBEGIN (*-explicit-constructor)
    Instruction(const InstructionData::TSTInstructionData& data);
    Instruction(const InstructionData::ORI_to_CCR_InstructionData& data);
    Instruction(const InstructionData::ORI_to_SR_InstructionData& data);
    Instruction(const InstructionData::ORI_InstructionData& data);
    
    //NOLINTEND


private:
    InstructionType type_;
    InstructionData::InstructionDataVariant data_;

};

} //namespace m68k