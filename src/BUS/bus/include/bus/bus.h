#pragma once
#include <cstdint>
#include <ibusdevice.h>
#include <memory>
#include <memoryinterface.h>
#include <optional>
#include <vector>

namespace DataExchange {

struct AddressRange {
    uint32_t start;
    uint32_t end;
};

struct DeviceParams {
    std::shared_ptr<IBusDevice> device;
    uint32_t baseAddress = 0;
    std::optional<AddressRange> readRange;
    std::optional<AddressRange> writeRange;
};

class Bus : public MemoryInterface {

public:
    Bus() = default;
    Bus(const Bus &) = default;
    Bus(Bus &&) = default;
    Bus &operator=(const Bus &) = default;
    Bus &operator=(Bus &&) = default;
    ~Bus() override = default;

    [[nodiscard]] std::expected<MemoryAccessResult, MemoryAccessError> read16(uint32_t address) const override;
    [[nodiscard]] std::expected<void, MemoryAccessError> write16(uint32_t address, uint16_t value) override;
    bool mapDevice(DeviceParams deviceParams);

private:

    enum class OperationType : uint8_t {
        READ,
        WRITE
    };

    struct DeviceMatcher {
        std::reference_wrapper<IBusDevice> device;
        uint32_t addressOffset = 0;
    };

    [[nodiscard]] std::optional<DeviceMatcher> findDevice(OperationType operationType, uint32_t address) const;
    [[nodiscard]] bool isAddressInRange(uint32_t address, const AddressRange& range) const;
    [[nodiscard]] bool canAddDevice(const DeviceParams& deviceParams) const;
    [[nodiscard]] AddressRange getRealAddressRange(const AddressRange& range, uint32_t baseAddress) const;

private:

    std::vector<DeviceParams> devices_;
};

} // namespace DataExchange