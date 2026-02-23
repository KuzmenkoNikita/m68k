#include <gtest/gtest.h>
#include <cpu/internal/bus_helper/bus_helper.h>
#include <expected>
#include <mock_bus.h>


TEST(BusHelpersTest, ReadFromUnmapped)
{
    m68k::BusHelpersTest::MockBus bus;
    
    EXPECT_CALL(bus, read16(0x00FF)).WillOnce(testing::Return(std::unexpected(DataExchange::MemoryAccessError::READ_FROM_UNMAPPED_ADDRESS)));

    const auto readResult = m68k::busHelper::read<uint16_t>(bus, 0x00FF);

    ASSERT_FALSE(readResult.has_value());
    EXPECT_EQ(readResult.error(), DataExchange::MemoryAccessError::READ_FROM_UNMAPPED_ADDRESS);
}

TEST(BusHelpersTest, ReadUint16)
{
    m68k::BusHelpersTest::MockBus bus;
    
    EXPECT_CALL(bus, read16(0x00FF)).WillOnce(testing::Return(DataExchange::MemoryAccessResult {
        .data = 0xABCD,
        .waitCycles = 4
    }));

    const auto readResult = m68k::busHelper::read<uint16_t>(bus, 0x00FF);

    ASSERT_TRUE(readResult.has_value());
    EXPECT_EQ(readResult.value().data, 0xABCD);
    EXPECT_EQ(readResult.value().waitCycles, 4);
}

TEST(BusHelpersTest, ReadInt16)
{
    m68k::BusHelpersTest::MockBus bus;
    
    EXPECT_CALL(bus, read16(0x00FF)).WillOnce(testing::Return(DataExchange::MemoryAccessResult {
        .data = 0xFFD6,
        .waitCycles = 4
    }));

    const auto readResult = m68k::busHelper::read<int16_t>(bus, 0x00FF);

    ASSERT_TRUE(readResult.has_value());
    EXPECT_EQ(readResult.value().data, -42);
    EXPECT_EQ(readResult.value().waitCycles, 4);
}

TEST(BusHelpersTest, ReadUint32)
{
    m68k::BusHelpersTest::MockBus bus;
    
    DataExchange::MemoryAccessResult highResult{.data=0x1234, .waitCycles=4};
    DataExchange::MemoryAccessResult lowResult{.data=0x5678, .waitCycles=3};
    
    EXPECT_CALL(bus, read16(0x0200))
        .WillOnce(testing::Return(highResult));
    EXPECT_CALL(bus, read16(0x0202))
        .WillOnce(testing::Return(lowResult));
    
    const auto readResult = m68k::busHelper::read<uint32_t>(bus, 0x0200);
    
    EXPECT_TRUE(readResult.has_value());
    EXPECT_EQ(readResult->data, 0x12345678);
    EXPECT_EQ(readResult->waitCycles, 7); 
}

TEST(BusHelpersTest, ReadUint8EvenAddress)
{
    m68k::BusHelpersTest::MockBus bus;
    
    DataExchange::MemoryAccessResult readResult{.data=0x1234, .waitCycles=4};
    
    EXPECT_CALL(bus, read16(0x0300))
        .WillOnce(testing::Return(readResult));
    
    const auto result = m68k::busHelper::read<uint8_t>(bus, 0x0300);
    
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result->data, 0x12); // старший байт
    EXPECT_EQ(result->waitCycles, 4);
}

TEST(BusHelpersTest, ReadUint8OddAddress)
{
    m68k::BusHelpersTest::MockBus bus;
    
    DataExchange::MemoryAccessResult readResult{.data=0x1234, .waitCycles=4};
    
    EXPECT_CALL(bus, read16(0x0301))
        .WillOnce(testing::Return(readResult));
    
    const auto result = m68k::busHelper::read<uint8_t>(bus, 0x0301);
    
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(result->data, 0x34); // младший байт
    EXPECT_EQ(result->waitCycles, 4);
}