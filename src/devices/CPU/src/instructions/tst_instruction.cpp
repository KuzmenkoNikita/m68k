#include <tst_instruction.h>

namespace m68k {

TSTInstruction::TSTInstruction(Data data) : 
                        length_{}
                        , data_(data)
{

}

size_t TSTInstruction::lengthImpl() const
{
    return length_;
}

} //namespace m68k