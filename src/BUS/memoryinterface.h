#pragma once
#include <cstdint>
/**
 * @file memoryinterface.h
 * @brief Abstract memory access interface for the m68k emulator.
 *
 * This header declares MemoryInterface — a minimal virtual interface that
 * emulator components (CPU, devices, memory backends) can implement to
 * provide 16-bit memory accesses used by the core.
 *
 * Implementations are responsible for:
 *  - Correct address range checks and bounds handling.
 *  - The emulator's chosen endianness (Motorola 68k is big-endian).
 *  - Any required alignment handling or access side-effects (e.g., memory-mapped I/O).
 *
 * The interface exposes only 16-bit reads/writes because the m68k fetches
 * instruction words and many effective-address transfers are word/long aligned.
 * Higher-level helpers can combine multiple 16-bit accesses if needed.
 *
 * Note: Methods are virtual and may be called frequently from the CPU hot path.
 * Implementations should minimize overhead; consider inlining or providing a
 * non-virtual fast-path if profiling shows this is a bottleneck.
 */

namespace DataExchange {

/**
 * @brief Minimal abstract interface for 16-bit memory accesses.
 *
 * Provide read16/write16 implementations to back the emulator memory model
 * or attach peripheral devices to the CPU bus. All addresses and values are
 * expressed in host integer types; semantics (e.g., alignment, endianness)
 * are implementation-defined and should follow the emulator convention.
 */
class MemoryInterface {
public:
  /** @brief Defaulted copy constructor: allows shallow copying of interface handles. */
  MemoryInterface(const MemoryInterface &) = default;

  /** @brief Deleted move constructor: moving an interface is not supported. */
  MemoryInterface(MemoryInterface &&) = delete;

  /** @brief Defaulted copy assignment operator. */
  MemoryInterface &operator=(const MemoryInterface &) = default;

  /** @brief Deleted move assignment operator. */
  MemoryInterface &operator=(MemoryInterface &&) = delete;

    /**
   * @brief Read a 16-bit value from the given byte address.
   * @param address Byte address to read from.
   * @return The 16-bit value read from memory.
   *
   * Implementations should define behaviour for out-of-range accesses (throw,
   * wrap, return 0xFFFF, etc.) and must document endianness. For m68k compatibility
   * the returned value is typically big-endian word assembled from memory bytes.
   */
  virtual uint16_t read16(uint32_t address) = 0;

    /**
   * @brief Write a 16-bit value to the given byte address.
   * @param address Byte address to write to.
   * @param value  16-bit value to write.
   *
   * Implementations must handle any alignment or side-effects required by
   * memory-mapped devices. Value byte-order semantics are implementation-defined
   * but should match read16.
   */
  virtual void write16(uint32_t address, uint16_t value) = 0;

  /** @brief Virtual destructor for safe polymorphic deletion. */
  virtual ~MemoryInterface() = default;
};

} // namespace DataExchange