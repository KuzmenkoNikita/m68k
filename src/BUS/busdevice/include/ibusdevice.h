#pragma once
#include <cstdint>

/**
 * @file ibusdevice.h
 * @brief Interface for memory-mapped bus devices used by the emulator.
 *
 * This header declares DataExchange::IBusDevice — a minimal abstract base
 * class that devices attached to the CPU bus should implement. The interface
 * exposes 16-bit read/write operations using byte addresses (Motorola 68k
 * uses big-endian semantics; implementations should document byte order).
 *
 * Implementations are expected to handle address range checks, alignment,
 * side-effects (MMIO) and any required synchronization if accessed from
 * multiple threads.
 */


namespace DataExchange {

/**
 * @brief Abstract base for bus-attached devices.
 *
 * Implement this interface to provide device-backed memory or MMIO that the
 * CPU core can read from and write to. The class is non-copyable and
 * non-movable to avoid accidental handle duplication.
 */
class IBusDevice {
public:
    /** @brief Default constructor. */
    IBusDevice() = default;
    
    /** @brief Virtual destructor for safe polymorphic deletion. */
    virtual ~IBusDevice() = default;

    /** @name Disabled special member functions */
    /// @{
    IBusDevice(const IBusDevice&) = delete;             ///< no copy
    IBusDevice& operator=(const IBusDevice&) = delete;  ///< no copy assign
    IBusDevice(IBusDevice&&) = delete;                  ///< no move
    IBusDevice& operator=(IBusDevice&&) = delete;       ///< no move assign
    /// @}

    /**
     * @brief Read a 16-bit value from the device at the given byte address.
     * @param addr Byte address to read from.
     * @return 16-bit value read from the device.
     *
     * Implementations should document behavior for out-of-range addresses.
     * For m68k semantics the value is typically assembled as a big-endian word.
     */
    virtual uint16_t read16(uint32_t addr) = 0;

    /**
     * @brief Write a 16-bit value to the device at the given byte address.
     * @param addr Byte address to write to.
     * @param val 16-bit value to write.
     *
     * Implementations must perform any necessary side-effects (register updates,
     * interrupts, etc.) and handle alignment/endian concerns consistent with
     * the emulator's conventions.
     */
    virtual void write16(uint32_t addr, uint16_t val) = 0;
};

} // namespace DataExchange