#pragma once
#include <concepts>
#include <expected>
#include <memoryinterface.h>

namespace m68k::busHelper {

template<typename T>
concept AllowedTypes = 
    std::same_as<T, std::uint8_t>  ||
    std::same_as<T, std::int8_t>   ||
    std::same_as<T, std::uint16_t> ||
    std::same_as<T, std::int16_t>  ||
    std::same_as<T, std::uint32_t> ||
    std::same_as<T, std::int32_t>;


template<class T>
requires AllowedTypes<T>
struct MemoryAccessResult {
    T data;
    int waitCycles; 
};

template<class DataType>
requires AllowedTypes<DataType>
std::expected<MemoryAccessResult<DataType>, DataExchange::MemoryAccessError> read(const DataExchange::MemoryInterface& bus, uint32_t address)
{
    if constexpr (std::is_same_v<DataType, std::uint8_t> || std::is_same_v<DataType, std::int8_t>) {

        auto readResult = bus.read16(address);
        if (!readResult) {
            return std::unexpected(readResult.error());
        }
        
        return MemoryAccessResult<DataType> {
            .data = static_cast<DataType>((address & 1U) ? (readResult->data & 0xFFU) : (readResult->data >> 8U)), //NOLINT(*-magic-numbers)
            .waitCycles = readResult->waitCycles
        };
    } 
    else if constexpr (std::is_same_v<DataType, std::uint16_t> || std::is_same_v<DataType, std::int16_t>) {

        auto readResult = bus.read16(address);
        if (!readResult) {
            return std::unexpected(readResult.error());
        }

        return MemoryAccessResult<DataType> {
            .data = static_cast<DataType>(readResult->data), 
            .waitCycles = readResult->waitCycles
        };
    }
    else if constexpr (std::is_same_v<DataType, std::uint32_t> || std::is_same_v<DataType, std::int32_t>) {

        auto highResult = bus.read16(address);
        if (!highResult) {
            return std::unexpected(highResult.error());
        }

        auto lowResult = bus.read16(address + 2);
        if (!lowResult) {
            return std::unexpected(lowResult.error());
        }

        return MemoryAccessResult<DataType> {
            .data = static_cast<DataType>((static_cast<uint32_t>(highResult->data) << 16U) | static_cast<uint32_t>(lowResult->data)), //NOLINT(*-magic-numbers)
            .waitCycles = highResult->waitCycles + lowResult->waitCycles
        };
    }
}



} // namespace m68k::busHelper