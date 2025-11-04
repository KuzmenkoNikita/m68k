cmake_minimum_required(VERSION 3.17.0)

add_executable(M68kBusTests
    bus_tests.cpp
)

target_link_libraries(M68kBusTests
    PRIVATE
    M68kBus
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
)

target_include_directories(M68kBusTests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/mock
)


add_test(NAME bus_tests COMMAND M68kBusTests)