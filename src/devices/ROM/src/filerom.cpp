#include "rom/filerom.h"
#include <fstream>

namespace DataExchange {

FileROM::FileROM(const char* filepath)
{
    std::ifstream file(filepath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + std::string(filepath));
    }

    auto size = file.tellg();
    file.seekg(0);
    romData_.resize(size);

    file.read(reinterpret_cast<char*>(romData_.data()), size); //NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
}

uint16_t FileROM::read16(uint32_t address)
{
    if (address + 1 >= romData_.size()) {
        throw std::out_of_range("Попытка чтения за пределами ROM: " + std::to_string(address));
    }

    /// big-endian assembly
    constexpr unsigned int shiftCount = 8;
    auto high = std::to_integer<uint32_t>(romData_[address]);
    auto low  = std::to_integer<uint32_t>(romData_[address + 1]);
    return static_cast<uint16_t>((high << shiftCount) | low);
}


void FileROM::write16(uint32_t /*address*/, uint16_t /*value*/)
{
    
};



}  // namespace DataExchange