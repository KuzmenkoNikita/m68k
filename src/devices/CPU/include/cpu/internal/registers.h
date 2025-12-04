#pragma once
#include <array>
#include <cstdint>

/**
 * @file registers.h
 * @brief CPU register definitions for the m68k emulator.
 *
 * This header declares the Registers struct which models the Motorola
 * 68000 CPU register state used by the emulator core. It includes
 * data registers, address registers, user and supervisor stack pointers,
 * program counter and a packed representation of the status register (SR).
 */

namespace m68k_ {

/**
 * @brief Status Register (SR).
 *
 * Packed representation of the 16-bit SR. The low byte contains the
 * condition code flags (X, N, Z, V, C). The high byte contains
 * interrupt mask, supervisor/user flag, master/interrupt state and trace bits.
 *
 * Note: Bitfield ordering here assumes typical little-endian target for storage,
 * but accessors should be used if strict portability or binary compatibility is required.
 */
struct StatusRegister{
    /// @name Condition code flags (lower byte)
    /// @{
    bool carry : 1;     ///< Carry flag (C)
    bool overflow : 1;  ///< Overflow flag (V)
    bool zero : 1;      ///< Zero flag (Z)
    bool negative : 1;  ///< Negative flag (N)
    bool extend : 1;    ///< Extend flag (X) - used by multiple arithmetic ops
    bool : 3;           ///< Padding to complete the lower byte
    /// @}
    /// @name System flags (upper byte)
    /// @{
    uint8_t interruptMask : 3;          ///< Interrupt priority mask (I2..I0)
    bool : 1;                           ///< Reserved / padding
    bool masterOrInterruptState : 1;    ///< Master/Interrupt state (M)
    bool supervisorOrUserState : 1;     ///< Supervisor/User state (S)
    uint8_t  trace : 2;                 ///< Trace mode bits (T1, T0)
    /// @}
};
/**
 * @brief Complete CPU register state for the emulator.
 *
 * Contains:
 *  - Data registers D0..D7
 *  - Address registers A0..A6 (A7 is represented via usp/ssp)
 *  - User and Supervisor stack pointers (usp, ssp)
 *  - Program counter (pc)
 *  - Status register (sr) broken out into condition codes and system flags
 */
struct Registers {

    /**
     * @brief Access a data register (read/write).
     *
     * @param regNum Index of the data register [0..7].
     * @return Reference to the 32-bit data register.
     *
     * @throws std::out_of_range if regNum is outside [0..7].
     */
    uint32_t& D(int regNum) 
    {
        return dataRegisters_.at(regNum);
    }

    /**
     * @brief Access a data register (read-only).
     *
     * @param regNum Index of the data register [0..7].
     * @return Const reference to the 32-bit data register.
     *
     * @throws std::out_of_range if regNum is outside [0..7].
     */
    [[nodiscard]] const uint32_t& D(int regNum) const
    {
        return dataRegisters_.at(regNum);
    }

    /**
     * @brief Access an address register (read/write).
     *
     * If regNum == 7, returns the active stack pointer (A7) depending on
     * the supervisor/user state stored in the SR.
     *
     * @param regNum Index of the address register [0..7] (7 is A7).
     * @return Reference to the 32-bit address register or active stack pointer.
     *
     * @throws std::out_of_range if regNum is outside [0..7) for normal A0..A6.
     */
    uint32_t& A(int regNum) 
    {
        if (regNum == 7) { //NOLINT(*-magic-numbers)
            return sr.supervisorOrUserState ? ssp : usp;
        }

        return addressRegisters_.at(regNum);
    }

    /**
     * @brief Access an address register (read-only).
     *
     * If regNum == 7, returns the active stack pointer (A7) depending on
     * the supervisor/user state stored in the SR.
     *
     * @param regNum Index of the address register [0..7] (7 is A7).
     * @return Const reference to the 32-bit address register or active stack pointer.
     *
     * @throws std::out_of_range if regNum is outside [0..7) for normal A0..A6.
     */
    [[nodiscard]] const uint32_t& A(int regNum) const 
    {
        if (regNum == 7) { //NOLINT(*-magic-numbers)
            return sr.supervisorOrUserState ? ssp : usp;
        }

        return addressRegisters_.at(regNum);
    }

    /**
     * @brief Get the Supervisor Stack Pointer (SSP).
     * @return Reference to the 32-bit supervisor stack pointer.
     */
    uint32_t& SSP() 
    { 
        return ssp; 
    }

    /**
     * @brief Get the Supervisor Stack Pointer (SSP) read-only.
     * @return Const reference to the 32-bit supervisor stack pointer.
     */
    [[nodiscard]] const uint32_t& SSP() const 
    { 
        return ssp; 
    }

    /**
     * @brief Get the User Stack Pointer (USP).
     * @return Reference to the 32-bit user stack pointer.
     */
    uint32_t& USP() 
    { 
        return usp; 
    }

    /**
     * @brief Get the User Stack Pointer (USP) read-only.
     * @return Const reference to the 32-bit user stack pointer.
     */
    [[nodiscard]] const uint32_t& USP() const
    { 
        return usp; 
    }

    /**
     * @brief Access the program counter (PC) for modification.
     * @return Reference to the 32-bit program counter.
     */
    uint32_t& PC() 
    { 
        return pc; 
    }

    /**
     * @brief Access the program counter (PC) read-only.
     * @return Const reference to the 32-bit program counter.
     */
    [[nodiscard]] const uint32_t& PC() const
    { 
        return pc; 
    }

    /**
     * @brief Access the status register (SR) for modification.
     * @return Reference to the StatusRegister struct.
     */
    StatusRegister& SR()
    {
        return sr;
    }

    /**
     * @brief Access the status register (SR) read-only.
     * @return Const reference to the StatusRegister struct.
     */
    [[nodiscard]] const StatusRegister& SR() const
    {
        return sr;
    }


private:
    /// @brief Data registers
    std::array<uint32_t, 8> dataRegisters_; //NOLINT(*-magic-numbers)

    /// @brief Address registers
    std::array<uint32_t, 7> addressRegisters_; //NOLINT(*-magic-numbers)

    /**
     * @brief User stack pointer (USP).
     *
     * The Motorola 68000 uses A7 as the active stack pointer. The emulator
     * stores separate usp/ssp values and will swap them when changing
     * between user and supervisor modes.
     */
    uint32_t usp;

    /**
     * @brief Supervisor stack pointer (SSP).
     *
     * Used when the CPU is in supervisor mode. See usp above.
     */
    uint32_t ssp;

    /**
     * @brief Program counter (PC).
     *
     * Holds the byte address of the next instruction to fetch.
     */
    uint32_t pc;

    /// @brief Status register (SR) containing condition codes and system flags.
    StatusRegister sr;
};
static_assert(sizeof(Registers) == 76, "Registers struct size must be 76 bytes"); //NOLINT

} // namespace m68k_