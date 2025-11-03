cmake_minimum_required(VERSION 3.17.0)

add_executable(M68kBusTests
    bus_tests.cpp
)

target_link_libraries(M68kBusTests
    PRIVATE
    M68kBus
    GTest::gtest
    GTest::gtest_main
)

# Регистрируем тест для ctest
add_test(NAME bus_tests COMMAND M68kBusTests)