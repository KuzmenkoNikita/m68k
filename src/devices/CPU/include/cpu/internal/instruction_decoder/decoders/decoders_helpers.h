#pragma once
#include <cpu/internal/instruction_decoder/instruction_decode_error.h>
#include <cpu/internal/instructions/data/addressing_mode_instruction_data.h>
#include <cpu/internal/instructions/instruction_params.h>
#include <expected>
#include <memoryinterface.h>
#include <variant>
#include <optional>

namespace m68k::decoders_ {

template <typename T, typename Variant>
struct is_type_in_variant;

template <typename T, typename... Ts>
struct is_type_in_variant<T, std::variant<Ts...>> {
    static constexpr bool value = (std::is_same_v<T, Ts> || ...);
};


template <typename T, typename Variant>
inline constexpr bool is_type_in_variant_v = is_type_in_variant<T, Variant>::value;


using addressingModesDataVariant =  std::variant<DataRegisterModeData,
                                                AddressRegisterModeData,
                                                AddressModeData,
                                                AddressWithPostincrementModeData,
                                                AddressWithPredecrementModeData,
                                                AddressWithDisplacementModeData,
                                                AddressWithIndexModeData,
                                                ProgramCounterWithDisplacementModeData,
                                                ProgramCounterWithIndexModeData,
                                                AbsoluteShortModeData,
                                                AbsoluteLongModeData,
                                                ImmediateModeData>;

template <typename AnyAddressingModeData>
std::optional<AnyAddressingModeData> convertAddressingModeData(const addressingModesDataVariant& allModes) {
    return std::visit([](const auto& item) -> std::optional<AnyAddressingModeData> {
        using T = std::decay_t<decltype(item)>;
        
        if constexpr (is_type_in_variant_v<T, AnyAddressingModeData>) {
            return item; 
        } else {
            return std::nullopt; 
        }
    }, allModes);
}

struct AddressingModeDataResult {
    addressingModesDataVariant data;
    uint32_t bytesReaded;
};

struct GetAddressingModeDataParams {
    OperationSize opSize;
    AddressingMode addressingMode;
    uint8_t registerValue;
    uint32_t instructionStartAddr;
};

std::expected<AddressingMode, DecodeError> getAddressingMode(uint8_t modeValue,  uint8_t registerValue);
std::expected<AddressingModeDataResult, DecodeError> getAddressingModeData(const DataExchange::MemoryInterface& bus, const GetAddressingModeDataParams& params);




} //namespace m68k::decoders_ 