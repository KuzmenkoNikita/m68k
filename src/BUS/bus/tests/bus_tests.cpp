#include "bus/bus.h"
#include "mock_bus_device.h"
#include <gtest/gtest.h>


TEST(BusTest, InvalidDeviceParamsMapping) {
    DataExchange::Bus bus;

    DataExchange::DeviceParams params;
    params.device = nullptr; 
    params.baseAddress = 0x0000;
    params.readRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT
    params.writeRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT

    EXPECT_FALSE(bus.mapDevice(std::move(params)));

    params.device = std::make_shared<BusTests::MockBusDevice>();
    params.readRange =  std::nullopt;
    params.writeRange = std::nullopt;

    EXPECT_FALSE(bus.mapDevice(std::move(params)));
}

TEST(BusTest, ReadWriteToUnmappedAddress) {
    DataExchange::Bus bus;

    auto readResult = bus.read16(0x1234); //NOLINT
    ASSERT_FALSE(readResult);
    EXPECT_EQ(readResult.error(), DataExchange::MemoryAccessError::READ_FROM_UNMAPPED_ADDRESS);

    auto writeResult = bus.write16(0x1234, 0xABCD); //NOLINT
    ASSERT_FALSE(writeResult);
    EXPECT_EQ(writeResult.error(), DataExchange::MemoryAccessError::WRITE_TO_UNMAPPED_ADDRESS);

    DataExchange::DeviceParams params;
    params.device = std::make_shared<BusTests::MockBusDevice>(); 
    params.baseAddress = 0x0000;
    params.readRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT
    params.writeRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT

    ASSERT_TRUE(bus.mapDevice(std::move(params)));

    readResult = bus.read16(0x100); //NOLINT
    ASSERT_FALSE(readResult);
    EXPECT_EQ(readResult.error(), DataExchange::MemoryAccessError::READ_FROM_UNMAPPED_ADDRESS);

    writeResult = bus.write16(0x100, 0xABCD); //NOLINT
    ASSERT_FALSE(writeResult);
    EXPECT_EQ(writeResult.error(), DataExchange::MemoryAccessError::WRITE_TO_UNMAPPED_ADDRESS);
}

TEST(BusTest, InterlacingMappingTest) {
    DataExchange::Bus bus;

    DataExchange::DeviceParams params1;
    params1.device = std::make_shared<BusTests::MockBusDevice>();
    params1.baseAddress = 0x0000;
    params1.readRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT
    params1.writeRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT

    ASSERT_TRUE(bus.mapDevice(std::move(params1)));

    DataExchange::DeviceParams params2;
    params2.device = std::make_shared<BusTests::MockBusDevice>();
    params2.baseAddress = 0x0080; //NOLINT
    params2.readRange = DataExchange::AddressRange{.start=0x0000, .end=0x007F}; //NOLINT
    params2.writeRange = DataExchange::AddressRange{.start=0x0000, .end=0x007F}; //NOLINT

    EXPECT_FALSE(bus.mapDevice(std::move(params2)));
}

TEST(BusTest, CorrectMappingTest) {
    DataExchange::Bus bus;

    DataExchange::DeviceParams params1;
    params1.device = std::make_shared<BusTests::MockBusDevice>();
    params1.baseAddress = 0x0000;
    params1.readRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT
    params1.writeRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT

    ASSERT_TRUE(bus.mapDevice(std::move(params1)));

    DataExchange::DeviceParams params2;
    params2.device = std::make_shared<BusTests::MockBusDevice>();
    params2.baseAddress = 0x0100; //NOLINT
    params2.readRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT
    params2.writeRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT

    EXPECT_TRUE(bus.mapDevice(std::move(params2)));

    DataExchange::DeviceParams params3;
    params2.device = std::make_shared<BusTests::MockBusDevice>();
    params2.baseAddress = 0x0100; //NOLINT
    params2.readRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT
    params2.writeRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT

    EXPECT_FALSE(bus.mapDevice(std::move(params2)));
}

TEST(BusTest, CorrectDeviceAddressCalculation) {
    DataExchange::Bus bus;

    auto device1 = std::make_shared<BusTests::MockBusDevice>();

    constexpr uint16_t writeValue = 0xBEEF; //NOLINT

    EXPECT_CALL(*device1, write16(0x80, writeValue)).Times(1);
    EXPECT_CALL(*device1, read16(0x50)).Times(1).WillOnce(testing::Return(0x1234)); //NOLINT

    DataExchange::DeviceParams params;
    params.device = device1;
    params.baseAddress = 0x1000; //NOLINT
    params.readRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT
    params.writeRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT

    ASSERT_TRUE(bus.mapDevice(std::move(params)));

    auto writeResult = bus.write16(0x1080, writeValue); //NOLINT
    ASSERT_TRUE(writeResult);
    auto readResult = bus.read16(0x1050); //NOLINT
    ASSERT_TRUE(readResult);
    EXPECT_EQ(readResult.value().data, 0x1234); //NOLINT
}

TEST(BusTest, ThreeDevicesMappedCorrectly) {
    DataExchange::Bus bus;

    auto device1 = std::make_shared<BusTests::MockBusDevice>();
    auto device2 = std::make_shared<BusTests::MockBusDevice>();
    auto device3 = std::make_shared<BusTests::MockBusDevice>();

    DataExchange::DeviceParams dev1Params;
    dev1Params.device = device1;
    dev1Params.baseAddress = 0x0000; //NOLINT
    dev1Params.readRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT
    dev1Params.writeRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT

    ASSERT_TRUE(bus.mapDevice(std::move(dev1Params)));

    DataExchange::DeviceParams dev2Params;
    dev2Params.device = device2;
    dev2Params.baseAddress = 0x0200; //NOLINT
    dev2Params.readRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT
    dev2Params.writeRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT

    ASSERT_TRUE(bus.mapDevice(std::move(dev2Params)));

    DataExchange::DeviceParams dev3Params;
    dev3Params.device = device3;
    dev3Params.baseAddress = 0x0400; //NOLINT
    dev3Params.readRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT
    dev3Params.writeRange = DataExchange::AddressRange{.start=0x0000, .end=0x00FF}; //NOLINT

    ASSERT_TRUE(bus.mapDevice(std::move(dev3Params)));

    EXPECT_CALL(*device1, write16(0x10, 0xAAAA)).Times(1);
    EXPECT_CALL(*device2, write16(0x20, 0xBBBB)).Times(1);
    EXPECT_CALL(*device3, write16(0x30, 0xCCCC)).Times(1);

    EXPECT_CALL(*device1, read16(0x20)).Times(1).WillOnce(testing::Return(0x1111)); //NOLINT
    EXPECT_CALL(*device2, read16(0x40)).Times(1).WillOnce(testing::Return(0x2222)); //NOLINT
    EXPECT_CALL(*device3, read16(0x60)).Times(1).WillOnce(testing::Return(0x3333)); //NOLINT

    auto writeResult1 = bus.write16(0x0010, 0xAAAA); //NOLINT
    ASSERT_TRUE(writeResult1);

    auto writeResult2 = bus.write16(0x0220, 0xBBBB); //NOLINT
    ASSERT_TRUE(writeResult2);

    auto writeResult3 = bus.write16(0x0430, 0xCCCC); //NOLINT
    ASSERT_TRUE(writeResult3); 

    auto readResult1 = bus.read16(0x0020); //NOLINT
    ASSERT_TRUE(readResult1);
    EXPECT_EQ(readResult1.value().data, 0x1111); //NOLINT

    auto readResult2 = bus.read16(0x0240); //NOLINT
    ASSERT_TRUE(readResult2);
    EXPECT_EQ(readResult2.value().data, 0x2222); //NOLINT

    auto readResult3 = bus.read16(0x0460); //NOLINT
    ASSERT_TRUE(readResult3);
    EXPECT_EQ(readResult3.value().data, 0x3333); //NOL
}
