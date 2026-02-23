cmake_minimum_required(VERSION 3.17.0)

set(EXECUTORS_TESTS 
    instructions_executors/tst_executor_tests.cpp
)

file(GLOB TEST_DATA_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/instructions_executors/json/*.json"
)

add_custom_target(copy_test_data ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${TEST_DATA_FILES}
    ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${TEST_DATA_FILES}
)



add_executable(CPUTests 
    ${EXECUTORS_TESTS}
    decoders_helpers_tests.cpp
    bus_helpers_tests.cpp
)

add_dependencies(CPUTests copy_test_data)

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


