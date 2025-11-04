#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <rom/filerom.h>

namespace {
class FileROMTest : public ::testing::Test {
protected:
    void SetUp() override {
        tempFile_ = std::tmpnam(nullptr); //NOLINT
        std::ofstream file(tempFile_, std::ios::binary);
        file.write(reinterpret_cast<const char*>(romData_.data()), romData_.size()); //NOLINT
        file.close();
    }

    void TearDown() override {
        std::filesystem::remove(tempFile_);
    }

    DataExchange::FileROM createROM() {
        return DataExchange::FileROM(tempFile_.c_str());
    }

    //NOLINTBEGIN
    std::array<std::byte, 8> romData_ = {
        std::byte{'S'}, std::byte{'E'},
        std::byte{'G'}, std::byte{'A'},
        std::byte{0x12}, std::byte{0x34},
        std::byte{0x56}, std::byte{0x78}
    };
    //NOLINTEND

private:
    std::string tempFile_;
};
} // namespace

TEST(ROMFileDeviceTest, invalidFilePathThrows) {

    EXPECT_THROW({
        DataExchange::FileROM rom("non_existent_file.rom");
    }, std::runtime_error);
} 

TEST_F(FileROMTest, ReadsBigEndianWordsCorrectly) {
    auto rom = createROM();
    EXPECT_EQ(rom.read16(0), 0x5345);
    EXPECT_EQ(rom.read16(2), 0x4741);
    EXPECT_EQ(rom.read16(4), 0x1234);
    EXPECT_EQ(rom.read16(6), 0x5678);
}

TEST_F(FileROMTest, ThrowsOnOutOfBoundsRead) {
    auto rom = createROM();
    EXPECT_THROW(rom.read16(100), std::out_of_range);
}

TEST_F(FileROMTest, HandlesEmptyFile) {
    std::string emptyFile = std::tmpnam(nullptr); //NOLINT
    std::ofstream(emptyFile, std::ios::binary).close();
    auto cleanup = [&]() { std::filesystem::remove(emptyFile); };

    EXPECT_THROW({
        DataExchange::FileROM rom(emptyFile.c_str());
        rom.read16(0);
    }, std::out_of_range);

    cleanup();
}