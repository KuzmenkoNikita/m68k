#pragma once
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
    /// @name Data registers
    /// @{
    uint32_t d0; ///< Data register D0 (32-bit)
    uint32_t d1; ///< Data register D1 (32-bit)
    uint32_t d2; ///< Data register D2 (32-bit)
    uint32_t d3; ///< Data register D3 (32-bit)
    uint32_t d4; ///< Data register D4 (32-bit)
    uint32_t d5; ///< Data register D5 (32-bit)
    uint32_t d6; ///< Data register D6 (32-bit)
    uint32_t d7; ///< Data register D7 (32-bit)
    /// @}

    /// @name Address registers
    /// @{
    uint32_t a0; ///< Address register A0 (32-bit)
    uint32_t a1; ///< Address register A1 (32-bit)
    uint32_t a2; ///< Address register A2 (32-bit)
    uint32_t a3; ///< Address register A3 (32-bit)
    uint32_t a4; ///< Address register A4 (32-bit)
    uint32_t a5; ///< Address register A5 (32-bit)
    uint32_t a6; ///< Address register A6 (32-bit / frame pointer)
    /// @}

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
    struct {
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
    }sr;
};
static_assert(sizeof(Registers) == 76, "Registers struct size must be 76 bytes");

} // namespace m68k_