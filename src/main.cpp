#include <bus/bus.h>
#include <rom/filerom.h>
#include <cpu/cpu.h>


int main(int, char**){

    DataExchange::Bus bus;

    auto rom = std::make_shared<DataExchange::FileROM>("/home/atreides/segaROMs/tt.gen");

    auto mapResult = bus.mapDevice(DataExchange::DeviceParams{
        .device = rom,
        .baseAddress = 0x000000,
        .readRange = DataExchange::AddressRange{.start=0x000000, .end=0x07FFFF}, //NOLINT
        .writeRange = std::nullopt
    });

    if (!mapResult) {
        throw std::runtime_error("Failed to map ROM device to bus.");
    }

    m68k::CPU cpu(std::make_shared<DataExchange::Bus>(bus));
    cpu.reset();

    while (true) {
        cpu.executeNextInstruction();
    }

    return 0;
}
