#pragma once
#include <cstddef>
#include <ibusdevice.h>
#include <vector>

/**
 * @file filerom.h
 * @brief File-backed read-only ROM device implementing DataExchange::IBusDevice.
 *
 * FileROM maps a binary file into an internal byte buffer and exposes 16-bit
 * big-endian read accesses via the IBusDevice interface. It is intended to
 * represent cartridge or BIOS ROM regions for the emulator.
 *
 * Behaviour notes:
 *  - Constructor loads the entire file into memory and throws std::runtime_error
 *    on open/read failure.
 *  - read16() assembles a big-endian 16-bit word from two consecutive bytes
 *    and throws std::out_of_range when accessing past the end of the image.
 *  - write16() is defined but the ROM is read-only; current behaviour is to
 *    ignore writes (implementations may choose to throw instead).
 *
 * Thread-safety: this class is not synchronized — callers must ensure safe
 * concurrent access if used from multiple threads.
 *
 * Example:
 * @code
 * DataExchange::FileROM rom("tt.gen");
 * uint16_t v = rom.read16(0x100);
 * @endcode
 */

namespace DataExchange {


class FileROM : public DataExchange::IBusDevice {
public:
    /**
    * @brief Construct and load ROM from file.
    * @param filepath Path to the ROM binary to load.
    *
    * Loads the entire file into an internal std::vector<std::byte>. Throws
    * std::runtime_error if the file cannot be opened or read.
    */
    explicit FileROM(const char* filepath);

    /**
     * @brief Read a 16-bit big-endian word from the ROM.
     * @param address Byte address within the ROM image.
     * @return 16-bit word assembled from romData_[address] (high byte) and
     *         romData_[address+1] (low byte).
     * @throws std::out_of_range if address+1 is outside the loaded image.
     */
    uint16_t read16(uint32_t address) override;

    /**
     * @brief Handle 16-bit writes to the ROM region.
     * @param address Byte address to write to.
     * @param value 16-bit value being written.
     *
     * ROM is read-only; this method currently ignores writes. Implementations
     * may alternatively throw to signal an invalid operation.
     */
    void write16(uint32_t address, uint16_t value) override;
private:            
    std::vector<std::byte> romData_; ///< Internal buffer holding the ROM image.
};
} // namespace DataExchange