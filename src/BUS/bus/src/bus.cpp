#include "bus/bus.h"
#include <algorithm>

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

    if (!canAddDevice(deviceParams)) {
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

        if (isAddressInRange(address, getRealAddressRange(range.value(), mapping.baseAddress)) && mapping.device) {

            return DeviceMatcher{
                .device = std::reference_wrapper<IBusDevice>(*mapping.device),
                .addressOffset = address - mapping.baseAddress
            };
        }
    }

    return std::nullopt;
}

bool Bus::canAddDevice(const DeviceParams& deviceParams) const
{
    if (!deviceParams.device) {
        return false;
    }

    if (!deviceParams.readRange && !deviceParams.writeRange) {
        return false;
    }

    auto overlaps = [](const AddressRange& lhs, const AddressRange& rhs) {
        return lhs.start <= rhs.end && rhs.start <= lhs.end;
    };

    auto noOverlapWithExisting = [&](const DeviceParams& existing) {
        if (!existing.readRange && !existing.writeRange) {
            return true;
        }

        if (deviceParams.readRange && existing.readRange && overlaps(getRealAddressRange(*existing.readRange, existing.baseAddress), 
                                                                    getRealAddressRange(*deviceParams.readRange, deviceParams.baseAddress))) {
            return false;
        }


        if (deviceParams.readRange && existing.writeRange && overlaps(getRealAddressRange(*existing.writeRange, existing.baseAddress),
                                                                     getRealAddressRange(*deviceParams.readRange, deviceParams.baseAddress))) {
            return false;
        }

        if (deviceParams.writeRange && existing.readRange && overlaps(getRealAddressRange(*existing.readRange, existing.baseAddress),
                                                                     getRealAddressRange(*deviceParams.writeRange, deviceParams.baseAddress))) {
            return false;
        }


        if (deviceParams.writeRange && existing.writeRange && overlaps(getRealAddressRange(*existing.writeRange, existing.baseAddress),
                                                                      getRealAddressRange(*deviceParams.writeRange, deviceParams.baseAddress))) {
            return false;
        }

        return true;
    };

    return std::ranges::all_of(devices_, noOverlapWithExisting);
}

AddressRange Bus::getRealAddressRange(const AddressRange& range, uint32_t baseAddress) const //NOLINT
{
    return AddressRange{
        .start = baseAddress + range.start,
        .end = baseAddress + range.end
    };
}

bool Bus::isAddressInRange(uint32_t address, const AddressRange& range) const //NOLINT
{
    return address >= range.start && address <= range.end;
}          

} // namespace DataExchange