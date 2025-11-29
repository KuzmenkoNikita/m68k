#include "cpu/internal/instruction_decoder/instruction_decode_error.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <cpu/internal/instruction_decoder/decoders/decoders_helpers.h>
#include <cpu/internal/instructions/data/addressing_mode_instruction_data.h>
#include <mock_bus.h>

namespace {

uint16_t getBriefExtensionWordValue(m68k::IndexedMode::BriefExtensionWord extensionWord)
{
    uint16_t resultValue = static_cast<uint8_t>(extensionWord.displacement);

    uint16_t sizeValue = static_cast<uint16_t>(extensionWord.indexSize) << 11U; //NOLINT(*-magic-numbers) 
    resultValue |= sizeValue;
    uint16_t registerValue = static_cast<uint16_t>(extensionWord.registerNum) << 12U; //NOLINT(*-magic-numbers) 
    resultValue |= registerValue;
    uint16_t regTypeValue = static_cast<uint16_t>(extensionWord.registerType) << 15U; //NOLINT(*-magic-numbers) 
    resultValue |= regTypeValue;

    return resultValue;
}


TEST(DecodersHelpersTests, getAddressingModeTest) 
{
    //NOLINTBEGIN(*-magic-numbers)
    auto result = m68k::decoders_::getAddressingMode(0,  7);
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), m68k::AddressingMode::DATA_REGISTER);

    result = m68k::decoders_::getAddressingMode(1,  2);
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), m68k::AddressingMode::ADDRESS_REGISTER);

    result = m68k::decoders_::getAddressingMode(2,  3);
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), m68k::AddressingMode::ADDRESS);

    result = m68k::decoders_::getAddressingMode(3,  4);
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), m68k::AddressingMode::ADDRESS_WITH_POSTINCREMENT);

    result = m68k::decoders_::getAddressingMode(4,  5);
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), m68k::AddressingMode::ADDRESS_WITH_PREDECREMENT);

    result = m68k::decoders_::getAddressingMode(5,  6);
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), m68k::AddressingMode::ADDRESS_WITH_DISPLACEMENT);

    result = m68k::decoders_::getAddressingMode(6,  7);
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), m68k::AddressingMode::ADDRESS_WITH_INDEX);

    result = m68k::decoders_::getAddressingMode(7,  2);
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), m68k::AddressingMode::PC_WITH_DISPLACEMENT);

    result = m68k::decoders_::getAddressingMode(7,  3);
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), m68k::AddressingMode::PC_WITH_INDEX);

    result = m68k::decoders_::getAddressingMode(7,  0);
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), m68k::AddressingMode::ABSOLUTE_SHORT);

    result = m68k::decoders_::getAddressingMode(7,  1);
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), m68k::AddressingMode::ABSOLUTE_LONG);

    result = m68k::decoders_::getAddressingMode(7,  4);
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), m68k::AddressingMode::IMMEDIATE);

    result = m68k::decoders_::getAddressingMode(0,  8);
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_ADDRESSING_MODE);

    result = m68k::decoders_::getAddressingMode(12,  8);
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_ADDRESSING_MODE);

    result = m68k::decoders_::getAddressingMode(9,  0);
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_ADDRESSING_MODE);

    result = m68k::decoders_::getAddressingMode(7,  5);
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_ADDRESSING_MODE);

    //NOLINTEND(*-magic-numbers)
} 

TEST(DecodersHelpersTests, getAddressingModeDataRegister) 
{
    //NOLINTBEGIN(*-magic-numbers)
    testing::StrictMock<m68k::BusHelpersTest::MockBus> strictBus;

    m68k::decoders_::GetAddressingModeDataParams params {
        .opSize = m68k::OperationSize::WORD,
        .addressingMode = m68k::AddressingMode::DATA_REGISTER,
        .registerValue = 2,
        .instructionStartAddr = 0x10000000
    };

    auto result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_TRUE(result.has_value());
    ASSERT_NO_THROW(std::get<m68k::DataRegisterModeData>(result->data));
    auto data = std::get<m68k::DataRegisterModeData>(result->data);
    EXPECT_EQ(data.dataRegNum, 2);

    ASSERT_ANY_THROW(std::get<m68k::AddressRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPostincrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPredecrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteShortModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteLongModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ImmediateModeData>(result->data));

    /* ************ */
    params.registerValue = 42;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_REGISTER_VALUE);

    /* ************ */
    params.registerValue = 7;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_NO_THROW(std::get<m68k::DataRegisterModeData>(result->data));
    data = std::get<m68k::DataRegisterModeData>(result->data);
    EXPECT_EQ(data.dataRegNum, 7);

    /* ************ */
    params.registerValue = 8;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_REGISTER_VALUE);

    /* ************ */
    params.registerValue = 0;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_NO_THROW(std::get<m68k::DataRegisterModeData>(result->data));
    data = std::get<m68k::DataRegisterModeData>(result->data);
    EXPECT_EQ(data.dataRegNum, 0);

    /* ************ */
    params.addressingMode = m68k::AddressingMode::NONE;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_ADDRESSING_MODE);
    //NOLINTEND(*-magic-numbers)
}

TEST(DecodersHelpersTests, getAddressingModeDataAddressRegister) 
{
    //NOLINTBEGIN(*-magic-numbers)
    testing::StrictMock<m68k::BusHelpersTest::MockBus> strictBus;

    m68k::decoders_::GetAddressingModeDataParams params {
        .opSize = m68k::OperationSize::WORD,
        .addressingMode = m68k::AddressingMode::ADDRESS_REGISTER,
        .registerValue = 2,
        .instructionStartAddr = 0x10000000
    };

    auto result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_TRUE(result.has_value());
    ASSERT_NO_THROW(std::get<m68k::AddressRegisterModeData>(result->data));
    auto data = std::get<m68k::AddressRegisterModeData>(result->data);
    EXPECT_EQ(data.addressRegNum, 2);

    ASSERT_ANY_THROW(std::get<m68k::DataRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPostincrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPredecrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteShortModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteLongModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ImmediateModeData>(result->data));

    /* ************ */
    params.registerValue = 42;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_REGISTER_VALUE);

    /* ************ */
    params.registerValue = 7;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_NO_THROW(std::get<m68k::AddressRegisterModeData>(result->data));
    data = std::get<m68k::AddressRegisterModeData>(result->data);
    EXPECT_EQ(data.addressRegNum, 7);

    /* ************ */
    params.registerValue = 8;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_REGISTER_VALUE);

    /* ************ */
    params.registerValue = 0;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_NO_THROW(std::get<m68k::AddressRegisterModeData>(result->data));
    data = std::get<m68k::AddressRegisterModeData>(result->data);
    EXPECT_EQ(data.addressRegNum, 0);

    /* ************ */
    params.addressingMode = m68k::AddressingMode::NONE;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_ADDRESSING_MODE);

    //NOLINTEND(*-magic-numbers)
}

TEST(DecodersHelpersTests, getAddressingModeDataAddressMode) 
{
    //NOLINTBEGIN(*-magic-numbers)

    testing::StrictMock<m68k::BusHelpersTest::MockBus> strictBus;

    m68k::decoders_::GetAddressingModeDataParams params {
        .opSize = m68k::OperationSize::WORD,
        .addressingMode = m68k::AddressingMode::ADDRESS,
        .registerValue = 2,
        .instructionStartAddr = 0x10000000
    };

    auto result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_TRUE(result.has_value());
    ASSERT_NO_THROW(std::get<m68k::AddressModeData>(result->data));
    auto data = std::get<m68k::AddressModeData>(result->data);
    EXPECT_EQ(data.addressRegNum, 2);

    ASSERT_ANY_THROW(std::get<m68k::DataRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPostincrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPredecrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteShortModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteLongModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ImmediateModeData>(result->data));

    /* ************ */
    params.registerValue = 42;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_REGISTER_VALUE);

    /* ************ */
    params.registerValue = 7;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_NO_THROW(std::get<m68k::AddressModeData>(result->data));
    data = std::get<m68k::AddressModeData>(result->data);
    EXPECT_EQ(data.addressRegNum, 7);

    /* ************ */
    params.registerValue = 8;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_REGISTER_VALUE);

    /* ************ */
    params.registerValue = 0;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_NO_THROW(std::get<m68k::AddressModeData>(result->data));
    data = std::get<m68k::AddressModeData>(result->data);
    EXPECT_EQ(data.addressRegNum, 0);

    /* ************ */
    params.addressingMode = m68k::AddressingMode::NONE;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_ADDRESSING_MODE);

    //NOLINTEND(*-magic-numbers)
}

TEST(DecodersHelpersTests, getAddressingModeDataAddressWithPostincrementMode) 
{
    //NOLINTBEGIN(*-magic-numbers)

    testing::StrictMock<m68k::BusHelpersTest::MockBus> strictBus;

    m68k::decoders_::GetAddressingModeDataParams params {
        .opSize = m68k::OperationSize::WORD,
        .addressingMode = m68k::AddressingMode::ADDRESS_WITH_POSTINCREMENT,
        .registerValue = 2,
        .instructionStartAddr = 0x10000000
    };

    auto result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_TRUE(result.has_value());
    ASSERT_NO_THROW(std::get<m68k::AddressWithPostincrementModeData>(result->data));
    auto data = std::get<m68k::AddressWithPostincrementModeData>(result->data);
    EXPECT_EQ(data.addressRegNum, 2);

    ASSERT_ANY_THROW(std::get<m68k::DataRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPredecrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteShortModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteLongModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ImmediateModeData>(result->data));

    /* ************ */
    params.registerValue = 42;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_REGISTER_VALUE);

    /* ************ */
    params.registerValue = 7;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_NO_THROW(std::get<m68k::AddressWithPostincrementModeData>(result->data));
    data = std::get<m68k::AddressWithPostincrementModeData>(result->data);
    EXPECT_EQ(data.addressRegNum, 7);

    /* ************ */
    params.registerValue = 8;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_REGISTER_VALUE);

    /* ************ */
    params.registerValue = 0;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_NO_THROW(std::get<m68k::AddressWithPostincrementModeData>(result->data));
    data = std::get<m68k::AddressWithPostincrementModeData>(result->data);
    EXPECT_EQ(data.addressRegNum, 0);

    /* ************ */
    params.addressingMode = m68k::AddressingMode::NONE;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_ADDRESSING_MODE);

    //NOLINTEND(*-magic-numbers)
}

TEST(DecodersHelpersTests, getAddressingModeDataAddressWithPredecrementMode) 
{
    //NOLINTBEGIN(*-magic-numbers)
    testing::StrictMock<m68k::BusHelpersTest::MockBus> strictBus;

    m68k::decoders_::GetAddressingModeDataParams params {
        .opSize = m68k::OperationSize::WORD,
        .addressingMode = m68k::AddressingMode::ADDRESS_WITH_PREDECREMENT,
        .registerValue = 2,
        .instructionStartAddr = 0x10000000
    };

    auto result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_TRUE(result.has_value());
    ASSERT_NO_THROW(std::get<m68k::AddressWithPredecrementModeData>(result->data));
    auto data = std::get<m68k::AddressWithPredecrementModeData>(result->data);
    EXPECT_EQ(data.addressRegNum, 2);

    ASSERT_ANY_THROW(std::get<m68k::DataRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPostincrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteShortModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteLongModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ImmediateModeData>(result->data));

    /* ************ */
    params.registerValue = 42;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_REGISTER_VALUE);

    /* ************ */
    params.registerValue = 7;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_NO_THROW(std::get<m68k::AddressWithPredecrementModeData>(result->data));
    data = std::get<m68k::AddressWithPredecrementModeData>(result->data);
    EXPECT_EQ(data.addressRegNum, 7);

    /* ************ */
    params.registerValue = 8;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_REGISTER_VALUE);

    /* ************ */
    params.registerValue = 0;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_NO_THROW(std::get<m68k::AddressWithPredecrementModeData>(result->data));
    data = std::get<m68k::AddressWithPredecrementModeData>(result->data);
    EXPECT_EQ(data.addressRegNum, 0);

    /* ************ */
    params.addressingMode = m68k::AddressingMode::NONE;
    result = m68k::decoders_::getAddressingModeData(strictBus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_ADDRESSING_MODE);
    //NOLINTEND(*-magic-numbers)
}

TEST(DecodersHelpersTests, getAddressingModeDataAddressWithDisplacementMode) 
{
    //NOLINTBEGIN(*-magic-numbers)
    m68k::BusHelpersTest::MockBus bus;
    
    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(std::unexpected(DataExchange::MemoryAccessError::READ_FROM_UNMAPPED_ADDRESS)));

    m68k::decoders_::GetAddressingModeDataParams params {
        .opSize = m68k::OperationSize::WORD,
        .addressingMode = m68k::AddressingMode::ADDRESS_WITH_DISPLACEMENT,
        .registerValue = 2,
        .instructionStartAddr = 0x10000000
    };

    auto result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::MEMORY_READ_FAILURE);

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(DataExchange::MemoryAccessResult{
        .data = 0xABCD,
        .waitCycles = 4
    }));

    result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_TRUE(result.has_value());

    ASSERT_ANY_THROW(std::get<m68k::DataRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPostincrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPredecrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteShortModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteLongModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ImmediateModeData>(result->data));

    EXPECT_NO_THROW(std::get<m68k::AddressWithDisplacementModeData>(result->data));

    auto data = std::get<m68k::AddressWithDisplacementModeData>(result->data);
    EXPECT_EQ(data.addressRegNum, 2);
    EXPECT_EQ(static_cast<uint16_t>(data.displacement), 0xABCD);

    //NOLINTEND(*-magic-numbers)
}

TEST(DecodersHelpersTests, getAddressingModeDataAddressWithIndexMode) 
{
    //NOLINTBEGIN(*-magic-numbers)
    m68k::BusHelpersTest::MockBus bus;

    m68k::decoders_::GetAddressingModeDataParams params {
        .opSize = m68k::OperationSize::WORD,
        .addressingMode = m68k::AddressingMode::ADDRESS_WITH_INDEX,
        .registerValue = 2,
        .instructionStartAddr = 0x10000000
    };

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(std::unexpected(DataExchange::MemoryAccessError::READ_FROM_UNMAPPED_ADDRESS)));

    auto result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::MEMORY_READ_FAILURE);

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(DataExchange::MemoryAccessResult{
        .data = 0xFFFF,
        .waitCycles = 4
    }));

    result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_BRIEF_EXTENSION_WORD);


    m68k::IndexedMode::BriefExtensionWord expectedExtensionWord {
        .displacement = -3,
        .indexSize = m68k::IndexedMode::IndexSize::WORD,
        .registerType = m68k::IndexedMode::RegisterType::ADDRESS_REGISTER,
        .registerNum = 3
    };

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(DataExchange::MemoryAccessResult{
        .data = getBriefExtensionWordValue(expectedExtensionWord),
        .waitCycles = 4
    }));

    result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_TRUE(result.has_value());

    ASSERT_ANY_THROW(std::get<m68k::DataRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPostincrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPredecrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteShortModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteLongModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ImmediateModeData>(result->data));

    EXPECT_NO_THROW(std::get<m68k::AddressWithIndexModeData>(result->data));

    auto data = std::get<m68k::AddressWithIndexModeData>(result->data);
    EXPECT_EQ(data.extensionWord.registerNum, 3);
    EXPECT_EQ(data.extensionWord.indexSize , m68k::IndexedMode::IndexSize::WORD);
    EXPECT_EQ(data.extensionWord.registerType , m68k::IndexedMode::RegisterType::ADDRESS_REGISTER);
    EXPECT_EQ(data.extensionWord.displacement , -3);

    params.registerValue = 12;
    result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_FALSE(result.has_value());
    //NOLINTEND(*-magic-numbers)
}

TEST(DecodersHelpersTests, getAddressingModeProgramCounterWithDisplacementMode) 
{
    //NOLINTBEGIN(*-magic-numbers)
    m68k::BusHelpersTest::MockBus bus;

    m68k::decoders_::GetAddressingModeDataParams params {
        .opSize = m68k::OperationSize::WORD,
        .addressingMode = m68k::AddressingMode::PC_WITH_DISPLACEMENT,
        .registerValue = 2,
        .instructionStartAddr = 0x10000000
    };

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(std::unexpected(DataExchange::MemoryAccessError::READ_FROM_UNMAPPED_ADDRESS)));
    auto result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::MEMORY_READ_FAILURE);

    params.registerValue = 12;
    result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_FALSE(result.has_value());

    params.registerValue = 3;

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(DataExchange::MemoryAccessResult{
        .data = 0xABCD,
        .waitCycles = 4
    }));

    result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_TRUE(result.has_value());

    ASSERT_ANY_THROW(std::get<m68k::DataRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPostincrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPredecrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteShortModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteLongModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ImmediateModeData>(result->data));

    EXPECT_NO_THROW(std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data));
    auto data = std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data);
    EXPECT_EQ(static_cast<uint16_t>(data.displacement), 0xABCD);
    //NOLINTEND(*-magic-numbers)
}

TEST(DecodersHelpersTests, getAddressingModeProgramCounterWithIndexMode) 
{
    //NOLINTBEGIN(*-magic-numbers)
    m68k::BusHelpersTest::MockBus bus;

    m68k::decoders_::GetAddressingModeDataParams params {
        .opSize = m68k::OperationSize::WORD,
        .addressingMode = m68k::AddressingMode::PC_WITH_INDEX,
        .registerValue = 2,
        .instructionStartAddr = 0x10000000
    };

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(std::unexpected(DataExchange::MemoryAccessError::READ_FROM_UNMAPPED_ADDRESS)));

    auto result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::MEMORY_READ_FAILURE);

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(DataExchange::MemoryAccessResult{
        .data = 0xFFFF,
        .waitCycles = 4
    }));

    result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::INVALID_BRIEF_EXTENSION_WORD);


    m68k::IndexedMode::BriefExtensionWord expectedExtensionWord {
        .displacement = -3,
        .indexSize = m68k::IndexedMode::IndexSize::WORD,
        .registerType = m68k::IndexedMode::RegisterType::ADDRESS_REGISTER,
        .registerNum = 3
    };

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(DataExchange::MemoryAccessResult{
        .data = getBriefExtensionWordValue(expectedExtensionWord),
        .waitCycles = 4
    }));

    result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_TRUE(result.has_value());

    ASSERT_ANY_THROW(std::get<m68k::DataRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPostincrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPredecrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteShortModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteLongModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ImmediateModeData>(result->data));

    EXPECT_NO_THROW(std::get<m68k::ProgramCounterWithIndexModeData>(result->data));

    auto data = std::get<m68k::ProgramCounterWithIndexModeData>(result->data);
    EXPECT_EQ(data.extensionWord.registerNum, 3);
    EXPECT_EQ(data.extensionWord.indexSize , m68k::IndexedMode::IndexSize::WORD);
    EXPECT_EQ(data.extensionWord.registerType , m68k::IndexedMode::RegisterType::ADDRESS_REGISTER);
    EXPECT_EQ(data.extensionWord.displacement , -3);

    params.registerValue = 12;
    result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_FALSE(result.has_value());
    //NOLINTEND(*-magic-numbers)
}

TEST(DecodersHelpersTests, getAddressingModeAbsoluteShortMode) 
{
    //NOLINTBEGIN(*-magic-numbers)
    m68k::BusHelpersTest::MockBus bus;

    m68k::decoders_::GetAddressingModeDataParams params {
        .opSize = m68k::OperationSize::WORD,
        .addressingMode = m68k::AddressingMode::ABSOLUTE_SHORT,
        .registerValue = 2,
        .instructionStartAddr = 0x10000000
    };

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(std::unexpected(DataExchange::MemoryAccessError::READ_FROM_UNMAPPED_ADDRESS)));
    auto result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::MEMORY_READ_FAILURE);

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(DataExchange::MemoryAccessResult{
        .data = 0xABCD,
        .waitCycles = 4
    }));

    result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_TRUE(result.has_value());

    ASSERT_ANY_THROW(std::get<m68k::DataRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPostincrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPredecrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteLongModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ImmediateModeData>(result->data));

    EXPECT_NO_THROW(std::get<m68k::AbsoluteShortModeData>(result->data));

    auto data = std::get<m68k::AbsoluteShortModeData>(result->data);
    EXPECT_EQ(data.address, 0xABCD);

    params.registerValue = 12;
    result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_FALSE(result.has_value());

    //NOLINTEND(*-magic-numbers)
}

TEST(DecodersHelpersTests, getAddressingModeAbsoluteLongMode) 
{
    //NOLINTBEGIN(*-magic-numbers)
    m68k::BusHelpersTest::MockBus bus;

    m68k::decoders_::GetAddressingModeDataParams params {
        .opSize = m68k::OperationSize::WORD,
        .addressingMode = m68k::AddressingMode::ABSOLUTE_LONG,
        .registerValue = 2,
        .instructionStartAddr = 0x10000000
    };

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(std::unexpected(DataExchange::MemoryAccessError::READ_FROM_UNMAPPED_ADDRESS)));
    auto result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::MEMORY_READ_FAILURE);

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(DataExchange::MemoryAccessResult{
        .data = 0xABCD,
        .waitCycles = 4
    }));

    EXPECT_CALL(bus, read16(0x10000004)).WillOnce(testing::Return(DataExchange::MemoryAccessResult{
        .data = 0x1234,
        .waitCycles = 4
    }));

    result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_TRUE(result.has_value());

    ASSERT_ANY_THROW(std::get<m68k::DataRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPostincrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPredecrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteShortModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ImmediateModeData>(result->data));

    EXPECT_NO_THROW(std::get<m68k::AbsoluteLongModeData>(result->data));

    auto data = std::get<m68k::AbsoluteLongModeData>(result->data);
    EXPECT_EQ(data.address, 0xABCD1234);

    params.registerValue = 12;
    result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_FALSE(result.has_value());

    //NOLINTEND(*-magic-numbers)
}

TEST(DecodersHelpersTests, getAddressingModeImmediateMode) 
{
    //NOLINTBEGIN(*-magic-numbers)
    m68k::BusHelpersTest::MockBus bus;

    m68k::decoders_::GetAddressingModeDataParams params {
        .opSize = m68k::OperationSize::BYTE,
        .addressingMode = m68k::AddressingMode::IMMEDIATE,
        .registerValue = 2,
        .instructionStartAddr = 0x10000000
    };

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(std::unexpected(DataExchange::MemoryAccessError::READ_FROM_UNMAPPED_ADDRESS)));
    auto result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), m68k::DecodeError::MEMORY_READ_FAILURE);

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(DataExchange::MemoryAccessResult{
        .data = 0xABCD,
        .waitCycles = 4
    }));

    result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_TRUE(result.has_value());

    ASSERT_ANY_THROW(std::get<m68k::DataRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressRegisterModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPostincrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithPredecrementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AddressWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithDisplacementModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::ProgramCounterWithIndexModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteShortModeData>(result->data));
    ASSERT_ANY_THROW(std::get<m68k::AbsoluteLongModeData>(result->data));

    EXPECT_NO_THROW(std::get<m68k::ImmediateModeData>(result->data));

    auto data = std::get<m68k::ImmediateModeData>(result->data);

    ASSERT_ANY_THROW(std::get<uint16_t>(data.immediateData));
    ASSERT_ANY_THROW(std::get<uint32_t>(data.immediateData));
    EXPECT_NO_THROW(std::get<uint8_t>(data.immediateData));
    EXPECT_EQ(std::get<uint8_t>(data.immediateData), 0xAB);

    params.opSize = m68k::OperationSize::WORD;

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(DataExchange::MemoryAccessResult{
        .data = 0xABCD,
        .waitCycles = 4
    }));

    result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_TRUE(result.has_value());

    data = std::get<m68k::ImmediateModeData>(result->data);

    ASSERT_ANY_THROW(std::get<uint8_t>(data.immediateData));
    ASSERT_ANY_THROW(std::get<uint32_t>(data.immediateData));
    EXPECT_NO_THROW(std::get<uint16_t>(data.immediateData));
    EXPECT_EQ(std::get<uint16_t>(data.immediateData), 0xABCD);

    params.opSize = m68k::OperationSize::LONG;

    EXPECT_CALL(bus, read16(0x10000002)).WillOnce(testing::Return(DataExchange::MemoryAccessResult{
        .data = 0xABCD,
        .waitCycles = 4
    }));

    EXPECT_CALL(bus, read16(0x10000004)).WillOnce(testing::Return(DataExchange::MemoryAccessResult{
        .data = 0x1234,
        .waitCycles = 4
    }));

    result = m68k::decoders_::getAddressingModeData(bus, params);
    ASSERT_TRUE(result.has_value());

    data = std::get<m68k::ImmediateModeData>(result->data);

    ASSERT_ANY_THROW(std::get<uint8_t>(data.immediateData));
    ASSERT_ANY_THROW(std::get<uint16_t>(data.immediateData));
    EXPECT_NO_THROW(std::get<uint32_t>(data.immediateData));
    EXPECT_EQ(std::get<uint32_t>(data.immediateData), 0xABCD1234);


    //NOLINTEND(*-magic-numbers)
}

} //namespace