cmake_minimum_required(VERSION 3.17.0)


add_executable(CPUTests 
    decoders_helpers_tests.cpp
    bus_helpers_tests.cpp
)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(CPUTests
    PRIVATE
    M68kCPUDevice
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
    nlohmann_json::nlohmann_json
)

add_test(NAME CPUTests COMMAND $<TARGET_FILE:CPUTests>)

target_include_directories(CPUTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/mock
)


