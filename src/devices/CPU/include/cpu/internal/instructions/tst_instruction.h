#pragma once
#include <instruction_base.h>
#include <instruction_params.h>
#include <data/instruction_data.h>

namespace m68k {

class TSTInstruction :  public InstructionBase<TSTInstruction> {
public:
    static constexpr InstructionType type =  InstructionType::TST;
    static constexpr bool hasData = true;
    static constexpr auto name = "TST";

    struct Data {
        AddressingMode addressingMode;
        OperationSize operationSize;
        union {
            DataRegisterModeData                    dataRegModeData;
            AddressRegisterModeData                 addressRegModeData;
            AddressModeData                         addressModeData;
            AddressWithPostincrementModeData        addressWithPostincrementModeData;
            AddressWithPredecrementModeData         addressWithPredecrementModeData;
            AddressWithDisplacementModeData         addressWithDisplacementModeData;
            AddressWithIndexModeData                addressWithIndexModeData;
            ProgramCounterWithDisplacementModeData  programCounterWithDisplacementModeData;
            ProgramCounterWithIndexModeData         programCounterWithIndexModeData;
            AbsoluteShortModeData                   absoluteShortModeData;
            AbsoluteLongModeData                    absoluteLongModeData;
            ImmediateModeData                       immediateModeData;
        }data;
    };

    explicit TSTInstruction(Data data);

    [[nodiscard]] size_t lengthImpl() const;

private:
    size_t length_;
    Data data_;
};

} //namespace m68k