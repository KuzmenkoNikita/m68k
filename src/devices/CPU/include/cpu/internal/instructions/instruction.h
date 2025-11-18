#pragma once
#include "instruction_params.h"
#include "data/instruction_data.h"
#include <utility>

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

    friend class InstructionsFactory;

private:
    Instruction(InstructionType type, InstructionData::InstructionDataVariant data) :
    type_(type)
    , data_(std::move(data)) {};
    
private:
    InstructionType type_;
    InstructionData::InstructionDataVariant data_;

};

} //namespace m68k