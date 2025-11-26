#pragma once
#include <cpu/internal/instruction_decoder/instruction_decode_error.h>
#include <cpu/internal/instructions/data/addressing_mode_instruction_data.h>
#include <cpu/internal/instructions/instruction_params.h>
#include <expected>
#include <memoryinterface.h>
#include <variant>

namespace m68k::decoders_ {


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