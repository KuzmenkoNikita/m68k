#include <gtest/gtest.h>
#include <cpu/internal/instruction_decoder/decoders/decoders_helpers.h>

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



} //namespace