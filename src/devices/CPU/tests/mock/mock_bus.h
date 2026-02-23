#include <gmock/gmock.h>
#include <memoryinterface.h>

namespace m68k::BusHelpersTest {

class MockBus: public DataExchange::MemoryInterface {
public:
    MOCK_METHOD((std::expected<DataExchange::MemoryAccessResult, DataExchange::MemoryAccessError>), read16, (uint32_t address), (const, override));
    MOCK_METHOD((std::expected<void, DataExchange::MemoryAccessError>), write16, (uint32_t address, uint16_t value), (override));
};

} // namespace m68k::BusHelpersTest