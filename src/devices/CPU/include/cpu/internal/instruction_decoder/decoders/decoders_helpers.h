#pragma once
#include <expected>
#include <instruction_decoder/instruction_decode_error.h>
#include <instructions/data/addressing_mode_instruction_data.h>
#include <instructions/instruction_params.h>
#include <variant>
#include <memory>
#include <memoryinterface.h>

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
    std::shared_ptr<DataExchange::MemoryInterface> bus;
};

std::expected<AddressingMode, DecodeError> getAddressingMode(uint8_t modeValue,  uint8_t registerValue);
std::expected<AddressingModeDataResult, DecodeError> getAddressingModeData(const GetAddressingModeDataParams& params);




} //namespace m68k::decoders_ 