cmake_minimum_required(VERSION 3.17.0)

add_executable(ROMFileDeviceTests
    romfile_device_tests.cpp
)

target_link_libraries(ROMFileDeviceTests
    PRIVATE
    ROMFileDevice
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
)

add_test(NAME rom_tests COMMAND ROMFileDeviceTests)