#include "instructions/instruction_params.h"
#include <bus_helper/bus_helper.h>
#include <expected>
#include <instruction_executor/executors/TST_executor.h>
#include <spdlog/spdlog.h>
#include <variant>

namespace m68k::executors_ {

namespace {

constexpr uint32_t BYTE_VALUE_MASK = 0x000000FFU;
constexpr uint32_t WORD_VALUE_MASK = 0x0000FFFFU;
constexpr uint32_t LONG_VALUE_MASK = 0xFFFFFFFFU;

constexpr uint32_t BYTE_SIGN_BIT_CHECK_MASK = 0x80U;
constexpr uint32_t WORD_SIGN_BIT_CHECK_MASK = 0x8000U;
constexpr uint32_t LONG_SIGN_BIT_CHECK_MASK = 0x80000000U;

constexpr uint8_t SP_REG_NUM = 7;


std::expected<uint32_t, ExecuteError> getMaskValueBySize(OperationSize size)
{
    uint32_t mask = 0;

    switch(size) {

        case OperationSize::BYTE: {
            mask = BYTE_VALUE_MASK;
            break;
        }

        case OperationSize::WORD: {
            mask = WORD_VALUE_MASK;
            break;
        }

        case OperationSize::LONG: {
            mask = LONG_VALUE_MASK;
            break;
        }

        default: {
            spdlog::error("Invalid operation size");
            return std::unexpected(ExecuteError::INVALID_OPERATION_SIZE);
        }
    }

    return mask;
}

std::expected<uint32_t, ExecuteError> readValueFromMemory(const DataExchange::MemoryInterface& bus, uint32_t address, OperationSize size)
{
    uint32_t value = 0;

    switch(size) {
        case OperationSize::BYTE: {

            const auto readResult = m68k::busHelper::read<uint8_t>(bus, address);
            if(!readResult){
                return std::unexpected(ExecuteError::MEMORY_READ_FAILURE);
            }

            value = readResult->data;
            break;
        }

        case OperationSize::WORD: {

            const auto readResult = m68k::busHelper::read<uint16_t>(bus, address);
            if(!readResult){
                return std::unexpected(ExecuteError::MEMORY_READ_FAILURE);
            }

            value = readResult->data;

            break;
        }

        case OperationSize::LONG: {

            const auto readResult = m68k::busHelper::read<uint32_t>(bus, address);
            if(!readResult){
                return std::unexpected(ExecuteError::MEMORY_READ_FAILURE);
            }

            value = readResult->data;
            break;
        }

        default: {
            return std::unexpected(ExecuteError::INVALID_OPERATION_SIZE);
        }
    }

    return value; 
}

int32_t getIndexValue(const m68k_::Registers& registers, const IndexedMode::BriefExtensionWord& extensionWord)
{
    const auto regValue = (extensionWord.registerType == IndexedMode::RegisterType::DATA_REGISTER) 
        ? registers.D(extensionWord.registerNum) 
        : registers.A(extensionWord.registerNum);

    if (extensionWord.indexSize == IndexedMode::IndexSize::WORD) {
        return static_cast<int16_t>(regValue & 0xFFFFU); //NOLINT (*-magic-numbers)
    }

    return static_cast<int32_t>(regValue);
}

}//namespace

TST_executor::TST_executor(std::shared_ptr<DataExchange::MemoryInterface> bus, 
                            std::shared_ptr<m68k_::Registers> registers) :
                            bus_(std::move(bus))
                            , registers_(std::move(registers))
{

}


std::expected<void, ExecuteError> TST_executor::execute(const Instruction& instruction)
{
    if(instruction.type() != InstructionType::TST) {
        spdlog::error("Invalid instruction type");
        return std::unexpected(ExecuteError::INVALID_INSTRUCTION);
    }

    const auto instructionData = instruction.data<InstructionData::TSTInstructionData>();

    const auto size = instructionData.size;

    return std::visit([this, &size](const auto& data) {
        return execute(data, size);
    }, instructionData.addressingModeData);

    return {};
}

std::expected<void, ExecuteError> TST_executor::execute(const DataRegisterModeData& data, OperationSize size)
{
    const auto maskValue = getMaskValueBySize(size);
    if(!maskValue) {
        spdlog::error("Failed to get mask for operation size");
        return std::unexpected(ExecuteError::INVALID_OPERATION_SIZE);        
    }

    setConditionCodes(registers_->D(data.dataRegNum) & maskValue.value(), size);

    return {};
}

std::expected<void, ExecuteError> TST_executor::execute(const AddressRegisterModeData& data, OperationSize size)
{
    const auto maskValue = getMaskValueBySize(size);
    if(!maskValue) {
        spdlog::error("Failed to get mask for operation size");
        return std::unexpected(ExecuteError::INVALID_OPERATION_SIZE);        
    }

    setConditionCodes(registers_->A(data.addressRegNum) & maskValue.value(), size);

    return {};
}

std::expected<void, ExecuteError> TST_executor::execute(const AddressModeData& data, OperationSize size)
{
    const uint32_t address =  registers_->A(data.addressRegNum);

    const auto readResult = readValueFromMemory(*bus_, address, size);
    if(!readResult){
        return std::unexpected(readResult.error());
    }

    const auto maskValue = getMaskValueBySize(size);
    if(!maskValue) {
        spdlog::error("Failed to get mask for operation size");
        return std::unexpected(ExecuteError::INVALID_OPERATION_SIZE);        
    }

    setConditionCodes(readResult.value() & maskValue.value(), size);

    return {};
}

std::expected<void, ExecuteError> TST_executor::execute(const AddressWithPostincrementModeData& data, OperationSize size)
{
    const uint32_t address =  registers_->A(data.addressRegNum);
    
    const auto readResult = readValueFromMemory(*bus_, address, size);
    if(!readResult){
        return std::unexpected(readResult.error());
    }

    if(size == OperationSize::BYTE && data.addressRegNum == SP_REG_NUM) {
        registers_->A(SP_REG_NUM) += 2;
    } else if (size == OperationSize::BYTE) {
        registers_->A(data.addressRegNum) += 1;
    } else if (size == OperationSize::WORD) {
        registers_->A(data.addressRegNum) += 2;
    } else if (size == OperationSize::LONG) {
        registers_->A(data.addressRegNum) += 4;
    }

    const auto maskValue = getMaskValueBySize(size);
    if(!maskValue) {
        spdlog::error("Failed to get mask for operation size");
        return std::unexpected(ExecuteError::INVALID_OPERATION_SIZE);        
    }

    setConditionCodes(readResult.value() & maskValue.value(), size);

    return {};
}

std::expected<void, ExecuteError> TST_executor::execute(const AddressWithPredecrementModeData& data, OperationSize size)
{
    if(size == OperationSize::BYTE && data.addressRegNum == SP_REG_NUM) {
        registers_->A(SP_REG_NUM) -= 2;
    } else if (size == OperationSize::BYTE) {
        registers_->A(data.addressRegNum) -= 1;
    } else if (size == OperationSize::WORD) {
        registers_->A(data.addressRegNum) -= 2;
    } else if (size == OperationSize::LONG) {
        registers_->A(data.addressRegNum) -= 4;
    }

    const uint32_t address =  registers_->A(data.addressRegNum);
    
    const auto readResult = readValueFromMemory(*bus_, address, size);
    if(!readResult){
        return std::unexpected(readResult.error());
    }

    const auto maskValue = getMaskValueBySize(size);
    if(!maskValue) {
        spdlog::error("Failed to get mask for operation size");
        return std::unexpected(ExecuteError::INVALID_OPERATION_SIZE);        
    }

    setConditionCodes(readResult.value() & maskValue.value(), size);

    return {};
}

std::expected<void, ExecuteError> TST_executor::execute(const AddressWithDisplacementModeData& data, OperationSize size)
{
    const uint32_t address =  registers_->A(data.addressRegNum) + data.displacement;

    const auto readResult = readValueFromMemory(*bus_, address, size);
    if(!readResult){
        return std::unexpected(readResult.error());
    }

    const auto maskValue = getMaskValueBySize(size);
    if(!maskValue) {
        spdlog::error("Failed to get mask for operation size");
        return std::unexpected(ExecuteError::INVALID_OPERATION_SIZE);        
    }

    setConditionCodes(readResult.value() & maskValue.value(), size);

    return {};
}

std::expected<void, ExecuteError> TST_executor::execute(const AddressWithIndexModeData& data, OperationSize size)
{
    const auto baseAddress =  registers_->A(data.addressRegNum);
    const auto indexValue = getIndexValue(*registers_, data.extensionWord);
    const auto address = baseAddress + data.extensionWord.displacement + indexValue;

    const auto readResult = readValueFromMemory(*bus_, address, size);
    if(!readResult){
        return std::unexpected(readResult.error());
    }

    const auto maskValue = getMaskValueBySize(size);
    if(!maskValue) {
        spdlog::error("Failed to get mask for operation size");
        return std::unexpected(ExecuteError::INVALID_OPERATION_SIZE);        
    }

    setConditionCodes(readResult.value() & maskValue.value(), size);
    return {};
}

std::expected<void, ExecuteError> TST_executor::execute(const ProgramCounterWithDisplacementModeData& data, OperationSize size)
{
    const auto address = registers_->PC() + data.displacement;

    const auto readResult = readValueFromMemory(*bus_, address, size);
    if(!readResult){
        return std::unexpected(readResult.error());
    }

    const auto maskValue = getMaskValueBySize(size);
    if(!maskValue) {
        spdlog::error("Failed to get mask for operation size");
        return std::unexpected(ExecuteError::INVALID_OPERATION_SIZE);        
    }

    setConditionCodes(readResult.value() & maskValue.value(), size);
    return {};
}

std::expected<void, ExecuteError> TST_executor::execute(const ProgramCounterWithIndexModeData& data, OperationSize size)
{
    const auto baseAddress =  registers_->PC();
    const auto indexValue = getIndexValue(*registers_, data.extensionWord);
    const auto address = baseAddress + data.extensionWord.displacement + indexValue;

    const auto readResult = readValueFromMemory(*bus_, address, size);
    if(!readResult){
        return std::unexpected(readResult.error());
    }

    const auto maskValue = getMaskValueBySize(size);
    if(!maskValue) {
        spdlog::error("Failed to get mask for operation size");
        return std::unexpected(ExecuteError::INVALID_OPERATION_SIZE);        
    }

    setConditionCodes(readResult.value() & maskValue.value(), size);
    return {};
}

std::expected<void, ExecuteError> TST_executor::execute(const AbsoluteShortModeData& data, OperationSize size)
{
    const uint32_t address =  data.address;

    const auto readResult = readValueFromMemory(*bus_, address, size);
    if(!readResult){
        return std::unexpected(readResult.error());
    }

    const auto maskValue = getMaskValueBySize(size);
    if(!maskValue) {
        spdlog::error("Failed to get mask for operation size");
        return std::unexpected(ExecuteError::INVALID_OPERATION_SIZE);        
    }

    setConditionCodes(readResult.value() & maskValue.value(), size);

    return {};
}

std::expected<void, ExecuteError> TST_executor::execute(const AbsoluteLongModeData& data, OperationSize size)
{
    const uint32_t address =  data.address;

    const auto readResult = readValueFromMemory(*bus_, address, size);
    if(!readResult){
        return std::unexpected(readResult.error());
    }

    const auto maskValue = getMaskValueBySize(size);
    if(!maskValue) {
        spdlog::error("Failed to get mask for operation size");
        return std::unexpected(ExecuteError::INVALID_OPERATION_SIZE);        
    }

    setConditionCodes(readResult.value() & maskValue.value(), size);

    return {};
}

std::expected<void, ExecuteError> TST_executor::execute(const ImmediateModeData& data, OperationSize size)
{
    uint32_t value = 0;

    switch(size) {
        case OperationSize::BYTE: {
            value = std::get<uint8_t>(data.immediateData);
            break;
        }

        case OperationSize::WORD: {
            value = std::get<uint16_t>(data.immediateData);
            break;
        }

        case OperationSize::LONG: {
            value = std::get<uint32_t>(data.immediateData);
            break;
        }

        default: {
            spdlog::error("Invalid operation size");
            return std::unexpected(ExecuteError::INVALID_OPERATION_SIZE);
        }
    }

    setConditionCodes(value, size);

    return {};
}

void TST_executor::setConditionCodes(uint32_t value, OperationSize size)
{
    registers_->SR().carry = false;
    registers_->SR().overflow = false;

    if (size == OperationSize::BYTE) {
        registers_->SR().negative = (value & BYTE_SIGN_BIT_CHECK_MASK) != 0;
    } else if (size == OperationSize::WORD) {
        registers_->SR().negative = (value & WORD_SIGN_BIT_CHECK_MASK) != 0;
    } else {
        registers_->SR().negative = (value & LONG_SIGN_BIT_CHECK_MASK) != 0;
    }

    registers_->SR().zero = value == 0;

}

} // namespace m68k::executors_