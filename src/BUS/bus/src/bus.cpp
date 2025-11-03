#include "bus/bus.h"

namespace DataExchange {

std::expected<MemoryAccessResult, MemoryAccessError> Bus::read16(uint32_t address)
{
    auto deviceOpt = findDevice(OperationType::READ, address);
    if (!deviceOpt.has_value()) {
        return std::unexpected(MemoryAccessError::READ_FROM_UNMAPPED_ADDRESS);
    }

    auto& [deviceRef, offset] = deviceOpt.value();
    uint16_t data = deviceRef.get().read16(offset); 

    return MemoryAccessResult{
        .data = data,
        .waitCycles = 0 // пока заглушка
    };
}

std::expected<void, MemoryAccessError> Bus::write16(uint32_t address, uint16_t value)
{
    auto deviceOpt = findDevice(OperationType::WRITE, address);
    if (!deviceOpt.has_value()) {
        return std::unexpected(MemoryAccessError::WRITE_TO_UNMAPPED_ADDRESS);
    }

    auto& [deviceRef, offset] = deviceOpt.value();
    deviceRef.get().write16(offset, value); 

    return {};
}

bool Bus::mapDevice(DeviceParams deviceParams)
{
    if (!deviceParams.device) {
        return false;
    }

    if (!canAddDevice(deviceParams.readRange, deviceParams.writeRange)) {
        return false;
    } 
          
    devices_.emplace_back(std::move(deviceParams));
    return true;
}

std::optional<Bus::DeviceMatcher> Bus::findDevice(OperationType operationType, uint32_t address) const
{
    for (const auto& mapping : devices_) {

        const auto& range = (operationType == OperationType::READ) ? mapping.readRange : mapping.writeRange;
        if (!range.has_value()) {
            continue;
        }

        if (isAddressInRange(address, range.value()) && mapping.device) {

            return DeviceMatcher{
                .device = std::reference_wrapper<IBusDevice>(*mapping.device),
                .addressOffset = address - mapping.baseAddress
            };
        }
    }

    return std::nullopt;
}

bool Bus::canAddDevice(std::optional<AddressRange> readRange, std::optional<AddressRange> writeRange) const
{
    if(!readRange && !writeRange) {
        return false;
    }

    auto overlaps = [](const AddressRange& a, const AddressRange& b) {
        return a.start <= b.end && b.start <= a.end;
    };

    for (const auto& existing : devices_) {

        if (readRange && existing.readRange && overlaps(*readRange, *existing.readRange)){
            return false;
        }

        if (readRange && existing.writeRange && overlaps(*readRange, *existing.writeRange)) {
            return false;
        }

        if (writeRange && existing.readRange && overlaps(*writeRange, *existing.readRange)) {
            return false;
        }
            
        if (writeRange && existing.writeRange && overlaps(*writeRange, *existing.writeRange)) {
            return false;
        }
    }

    return true;
}

bool Bus::isAddressInRange(uint32_t address, const AddressRange& range) const //NOLINT
{
    return address >= range.start && address <= range.end;
}          

} // namespace DataExchange