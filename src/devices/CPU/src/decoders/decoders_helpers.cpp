#include <bus_helper/bus_helper.h>
#include <cstdint>
#include <instruction_decoder/decoders/decoders_helpers.h>

namespace m68k::decoders_ {

namespace {
    constexpr uint8_t DATA_REGISTER_MODE_VALUE = 0;
    constexpr uint8_t ADDRESS_REGISTER_MODE_VALUE = 1;
    constexpr uint8_t ADDRESS_MODE_VALUE = 2;
    constexpr uint8_t ADDRESS_WITH_POSTINCREMENT_MODE_VALUE = 3;
    constexpr uint8_t ADDRESS_WITH_PREDECREMENT_MODE_VALUE = 4;
    constexpr uint8_t ADDRESS_WITH_DISPLACEMENT_MODE_VALUE = 5;
    constexpr uint8_t ADDRESS_WITH_INDEX_MODE_VALUE = 6;

    constexpr uint8_t EXTENDED_MODES_VALUE = 7;


    constexpr uint8_t ABSOLUTE_SHORT_REGISTER_VALUE = 0;
    constexpr uint8_t ABSOLUTE_LONG_REGISTER_VALUE = 1;
    constexpr uint8_t PC_WITH_DISPLACEMENT_REGISTER_VALUE = 2;
    constexpr uint8_t PC_WITH_INDEX_REGISTER_VALUE = 3;
    constexpr uint8_t IMMEDIATRE_REGISTER_VALUE = 4;

    constexpr uint8_t BRIEF_EXT_WORD_DISPLACEMENT_MASK = 0x00FFU;
    constexpr uint8_t BRIEF_EXT_WORD_INDEX_SIZE_MASK = 0x0800U;
    constexpr uint8_t BRIEF_EXT_WORD_INDEX_SIZE_POS = 11;
    constexpr uint8_t BRIEF_EXT_WORD_REG_NUM_MASK = 0x7000U;
    constexpr uint8_t BRIEF_EXT_WORD_REG_NUM_POS = 12;
    constexpr uint8_t BRIEF_EXT_WORD_REG_TYPE_MASK = 0x8000U;
    constexpr uint8_t BRIEF_EXT_WORD_REG_TYPE_POS = 15;

    IndexedMode::BriefExtensionWord getExtensionWord(uint16_t extensionWord)
    {
        IndexedMode::BriefExtensionWord result{};

        static_assert(static_cast<uint8_t>(IndexedMode::IndexSize::WORD) == 0);
        static_assert(static_cast<uint8_t>(IndexedMode::IndexSize::LONG) == 1);

        static_assert(static_cast<uint8_t>(IndexedMode::RegisterType::DATA_REGISTER) == 0);
        static_assert(static_cast<uint8_t>(IndexedMode::RegisterType::ADDRESS_REGISTER) == 1);

        result.displacement = static_cast<int8_t>(extensionWord & BRIEF_EXT_WORD_DISPLACEMENT_MASK);
        result.indexSize = static_cast<IndexedMode::IndexSize>(static_cast<uint16_t>(extensionWord & BRIEF_EXT_WORD_INDEX_SIZE_MASK) >> BRIEF_EXT_WORD_INDEX_SIZE_POS);
        result.registerNum = static_cast<uint8_t>(static_cast<uint16_t>(extensionWord & BRIEF_EXT_WORD_REG_NUM_MASK) >> BRIEF_EXT_WORD_REG_NUM_POS);
        result.registerType = static_cast<IndexedMode::RegisterType>(static_cast<uint16_t>(extensionWord & BRIEF_EXT_WORD_REG_TYPE_MASK) >> BRIEF_EXT_WORD_REG_TYPE_POS);

        return result;
    }
} // namespace

std::expected<AddressingMode, DecodeError> getAddressingMode(uint8_t modeValue,  uint8_t registerValue)
{
    if(registerValue > 7 || modeValue > 7) { //NOLINT(*-magic-numbers)
        return std::unexpected(DecodeError::INVALID_ADDRESSING_MODE);
    }

    switch(modeValue) {

        case DATA_REGISTER_MODE_VALUE: return AddressingMode::DATA_REGISTER;
        case ADDRESS_REGISTER_MODE_VALUE: return AddressingMode::ADDRESS_REGISTER;
        case ADDRESS_MODE_VALUE: return AddressingMode::ADDRESS;
        case ADDRESS_WITH_POSTINCREMENT_MODE_VALUE: return AddressingMode::ADDRESS_WITH_POSTINCREMENT;
        case ADDRESS_WITH_PREDECREMENT_MODE_VALUE: return AddressingMode::ADDRESS_WITH_PREDECREMENT;
        case ADDRESS_WITH_DISPLACEMENT_MODE_VALUE: return AddressingMode::ADDRESS_WITH_DISPLACEMENT;
        case ADDRESS_WITH_INDEX_MODE_VALUE: return AddressingMode::ADDRESS_WITH_INDEX;

        case EXTENDED_MODES_VALUE: {

            switch(registerValue) {
                case ABSOLUTE_SHORT_REGISTER_VALUE: return AddressingMode::ABSOLUTE_SHORT;
                case ABSOLUTE_LONG_REGISTER_VALUE: return AddressingMode::ABSOLUTE_LONG;
                case PC_WITH_DISPLACEMENT_REGISTER_VALUE: return AddressingMode::PC_WITH_DISPLACEMENT;
                case PC_WITH_INDEX_REGISTER_VALUE: return AddressingMode::PC_WITH_INDEX;
                case IMMEDIATRE_REGISTER_VALUE: return AddressingMode::IMMEDIATE;
                default: return std::unexpected(DecodeError::INVALID_ADDRESSING_MODE);
            }

            break;
        }


        default: {
            return std::unexpected(DecodeError::INVALID_ADDRESSING_MODE);
        }
    }
}

std::expected<AddressingModeDataResult, DecodeError> getAddressingModeData(const GetAddressingModeDataParams& params)
{
    switch(params.addressingMode) {
        case AddressingMode::DATA_REGISTER: return AddressingModeDataResult{.data=DataRegisterModeData{.dataRegNum = params.registerValue}, .bytesReaded=0};
        case AddressingMode::ADDRESS_REGISTER: return AddressingModeDataResult{.data=AddressRegisterModeData{.addressRegNum = params.registerValue}, .bytesReaded=0};
        case AddressingMode::ADDRESS: return AddressingModeDataResult{.data=AddressModeData{.addressRegNum = params.registerValue}, .bytesReaded=0};
        case AddressingMode::ADDRESS_WITH_POSTINCREMENT: return AddressingModeDataResult{.data=AddressWithPostincrementModeData{.addressRegNum = params.registerValue}, .bytesReaded=0};
        case AddressingMode::ADDRESS_WITH_PREDECREMENT: return AddressingModeDataResult{.data=AddressWithPredecrementModeData{.addressRegNum = params.registerValue}, .bytesReaded=0};
        case AddressingMode::ADDRESS_WITH_DISPLACEMENT: {

            const auto readResult = m68k::busHelper::read<int16_t>(*params.bus, params.instructionStartAddr + 2);
            if(!readResult) {
                return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
            }

            return AddressingModeDataResult{.data=AddressWithDisplacementModeData{.addressRegNum = params.registerValue, .displacement = readResult->data}, .bytesReaded=2};
        }

        case AddressingMode::ADDRESS_WITH_INDEX: {

            const auto readResult = m68k::busHelper::read<uint16_t>(*params.bus, params.instructionStartAddr + 2);
            if(!readResult) {
                return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
            }

            return AddressingModeDataResult{.data=AddressWithIndexModeData{.addressRegNum =params.registerValue, .extensionWord = getExtensionWord(readResult->data)}, .bytesReaded = 2};
        }

        case AddressingMode::PC_WITH_DISPLACEMENT: {

            const auto readResult = m68k::busHelper::read<int16_t>(*params.bus, params.instructionStartAddr + 2);
            if(!readResult) {
                return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
            }

            return AddressingModeDataResult{.data = ProgramCounterWithDisplacementModeData{.displacement = readResult->data}, .bytesReaded = 2};
        }

        case AddressingMode::PC_WITH_INDEX: {

            const auto readResult = m68k::busHelper::read<uint16_t>(*params.bus, params.instructionStartAddr + 2);
            if(!readResult) {
                return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
            }

            return AddressingModeDataResult{.data = ProgramCounterWithIndexModeData{.extensionWord = getExtensionWord(readResult->data)}, .bytesReaded = 2};
        }

        case AddressingMode::ABSOLUTE_SHORT: {

            const auto readResult = m68k::busHelper::read<uint16_t>(*params.bus, params.instructionStartAddr + 2);
            if(!readResult) {
                return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
            }

            return AddressingModeDataResult{.data = AbsoluteShortModeData{.address = readResult->data}, .bytesReaded = 2};
        }

        case AddressingMode::ABSOLUTE_LONG: {

            const auto readResult = m68k::busHelper::read<uint32_t>(*params.bus, params.instructionStartAddr + 2);
            if(!readResult) {
                return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
            }

            return AddressingModeDataResult{.data = AbsoluteLongModeData{.address = readResult->data}, .bytesReaded = 4};
        }

        case AddressingMode::IMMEDIATE: {

            ImmediateModeData data{};

            switch(params.opSize) {

                case OperationSize::BYTE: {

                    const auto readResult = m68k::busHelper::read<uint8_t>(*params.bus, params.instructionStartAddr + 2);
                    if(!readResult) {
                        return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
                    }

                    data.immediateData.byteData = readResult->data; //NOLINT(*-union-access)

                    return AddressingModeDataResult{.data = data, .bytesReaded = 2};
                }

                case OperationSize::WORD: {

                    const auto readResult = m68k::busHelper::read<uint16_t>(*params.bus, params.instructionStartAddr + 2);
                    if(!readResult) {
                        return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
                    }

                    data.immediateData.wordData = readResult->data; //NOLINT(*-union-access)
                    return AddressingModeDataResult{.data = data, .bytesReaded = 2};
                }

                case OperationSize::LONG: {
                    
                    const auto readResult = m68k::busHelper::read<uint32_t>(*params.bus, params.instructionStartAddr + 2);
                    if(!readResult) {
                        return std::unexpected(DecodeError::MEMORY_READ_FAILURE);
                    }

                    data.immediateData.longData = readResult->data; //NOLINT(*-union-access)
                    return AddressingModeDataResult{.data = data, .bytesReaded = 4};
                }

                default: {
                    return std::unexpected(DecodeError::INVALID_INSTRUCTION);
                }
            }
        }

        default: {
            return std::unexpected(DecodeError::INVALID_ADDRESSING_MODE);
        }
    }
}

} //namespace m68k::decoders_ 