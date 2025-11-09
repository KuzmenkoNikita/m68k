#pragma once
#include <cstdint>

namespace m68k {

namespace IndexedMode {

enum class RegisterType : uint8_t {
    DATA_REGISTER = 0,
    ADDRESS_REGISTER = 1
};

enum class IndexSize : uint8_t {
    WORD,
    LONG
};

} // namespace IndexedMode

struct DataRegisterModeData
{
    uint8_t dataRegNum : 3;
};

struct AddressRegisterModeData
{
    uint8_t addressRegNum : 3;
};

struct AddressModeData
{
    uint8_t addressRegNum : 3;
};

struct AddressWithPostincrementModeData
{
    uint8_t addressRegNum : 3;
};

struct AddressWithPredecrementModeData
{
    uint8_t addressRegNum : 3;
};

struct AddressWithDisplacementModeData
{
    uint8_t adressRegNum : 3;
    int16_t displacement;
};

struct AddressWithIndexModeData
{
    uint8_t adressRegNum : 3;
    int8_t displacement;
    IndexedMode::RegisterType registerType;
    IndexedMode::IndexSize indexSize;
    uint8_t registerNum : 3;
};

struct ProgramCounterWithDisplacementModeData
{
    uint16_t displacement;
};

struct ProgramCounterWithIndexModeData
{
    int8_t displacement;
    IndexedMode::IndexSize indexSize;
    IndexedMode::RegisterType registerType;
    uint8_t registerNum : 3;
};

struct AbsoluteShortModeData
{
    uint16_t address;
};

struct AbsoluteLongModeData
{
    uint32_t address;
};

struct ImmediateModeData
{
    union {
        uint8_t byteData;
        uint16_t wordData;
        uint32_t longData;
    }immediateData;
};


} // namespace m68k
