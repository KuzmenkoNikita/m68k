cmake_minimum_required(VERSION 3.17.0)

add_executable(CPUTests
    decoders_helpers_tests.cpp
)

target_link_libraries(CPUTests
    PRIVATE
    M68kCPUDevice
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
)

add_test(NAME CPUTests COMMAND $<TARGET_FILE:CPUTests>)