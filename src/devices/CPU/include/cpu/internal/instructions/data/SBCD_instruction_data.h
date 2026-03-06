#pragma once
#include <cstdint>


namespace m68k::InstructionData {

struct SBCD_InstructionData {

    enum class Operation : uint8_t {
        DATA_REG_TO_DATA_REG,
        MEM_TO_MEM
    };

    Operation operationType;
    uint8_t destinationRegister;
    uint8_t sourceRegister;

}; 


} //namespace m68k::InstructionData