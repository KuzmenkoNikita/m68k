#pragma once
#include <expected>
#include <instruction_decoder/decode_result.h>
#include <instruction_decoder/instruction_decode_error.h>
#include <memory>
#include <memoryinterface.h>

namespace m68k::decoders_ {

template<typename Derived>
class BaseDecoder {
public:

    explicit BaseDecoder(std::shared_ptr<DataExchange::MemoryInterface> bus) : bus_(std::move(bus)) {};

    [[nodiscard]] std::expected<DecodeResult, DecodeError> decode(uint16_t opcodeWord, uint32_t instructionStartAddr) const {

        return static_cast<const Derived*>(this)->decodeImpl(opcodeWord, instructionStartAddr);
    }

protected:
    std::shared_ptr<DataExchange::MemoryInterface> bus_; //NOLINT(*-non-private-member-variables-in-classes)
};

} // namespace m68k::decoders_