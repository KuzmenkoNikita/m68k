#pragma once
#include <cstdint>
#include <expected>

namespace DataExchange {

enum class MemoryAccessError : uint8_t {
    READ_FROM_UNMAPPED_ADDRESS,
    WRITE_TO_UNMAPPED_ADDRESS
};

struct MemoryAccessResult {
    uint16_t data;
    int waitCycles; 
};

class MemoryInterface {
public:
    MemoryInterface() = default;
    MemoryInterface(const MemoryInterface &) = default;
    MemoryInterface(MemoryInterface &&) = default;
    MemoryInterface &operator=(const MemoryInterface &) = default;
    MemoryInterface &operator=(MemoryInterface &&) = default;

    [[nodiscard]] virtual std::expected<MemoryAccessResult, MemoryAccessError> read16(uint32_t address) const = 0;
    [[nodiscard]] virtual std::expected<void, MemoryAccessError> write16(uint32_t address, uint16_t value) const = 0;
    virtual ~MemoryInterface() = default;
};

} // namespace DataExchange