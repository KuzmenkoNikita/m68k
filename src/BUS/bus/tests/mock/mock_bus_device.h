#pragma once
#include <gmock/gmock.h>
#include <ibusdevice.h>

namespace BusTests {

class MockBusDevice : public DataExchange::IBusDevice {
public:
    MOCK_METHOD(uint16_t, read16, (uint32_t offset), (override));
    MOCK_METHOD(void, write16, (uint32_t offset, uint16_t value), (override));
};

} // namespace BusTests