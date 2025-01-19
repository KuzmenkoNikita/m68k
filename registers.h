#include "types.h"

struct Registers {
    /// @brief Data registers
    LongWord d0;
    LongWord d1;
    LongWord d2;
    LongWord d3;
    LongWord d4;
    LongWord d5;
    LongWord d6;
    LongWord d7;

    /// @brief Addres registers
    LongWord a0;
    LongWord a1;
    LongWord a2;
    LongWord a3;
    LongWord a4;
    LongWord a5;
    LongWord a6;

    /// @brief User stack pointer
    LongWord usp;

    /// @brief Supervisor stack pointer
    LongWord ssp;

    /// @brief  Program counter
    LongWord pc;

    /// @brief Status register
    struct {
        /// @brief Lower (User) byte Condition codes
        bool carry : 1;
        bool overflow : 1;
        bool zero : 1;
        bool negative : 1;
        bool extend : 1;
        bool : 3;

        /// @brief Upper (system) byte
        uint8_t interruptMask : 3;
        bool : 1;
        bool masterOrInterruptState : 1;
        bool supervisorOrUserState : 1;
        uint8_t  trace : 2; 
    }sr;
};
static_assert(sizeof(Registers) == 76);