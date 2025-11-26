#include "cpu/internal/instruction_decoder/instruction_decode_error.h"
#include <gtest/gtest.h>
#include <cpu/internal/instruction_decoder/decoders/decoders_helpers.h>
#include <mock_bus.h>

namespace {

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

}



} //namespace