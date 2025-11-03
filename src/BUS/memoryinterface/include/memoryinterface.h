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
    MemoryInterface(MemoryInterface &&) = delete;
    MemoryInterface &operator=(const MemoryInterface &) = default;
    MemoryInterface &operator=(MemoryInterface &&) = delete;

    virtual std::expected<MemoryAccessResult, MemoryAccessError> read16(uint32_t address) = 0;
    virtual std::expected<void, MemoryAccessError> write16(uint32_t address, uint16_t value) = 0;
    virtual ~MemoryInterface() = default;
};

} // namespace DataExchange