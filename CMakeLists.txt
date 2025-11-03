cmake_minimum_required(VERSION 3.17.0)
project(m68k VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)

option(BUILD_TESTS "Build tests" ON)

add_executable(m68k src/main.cpp)

add_subdirectory(src/BUS/busdevice)
add_subdirectory(src/BUS/memoryinterface)
add_subdirectory(src/BUS/bus)
add_subdirectory(src/devices/ROM)
add_subdirectory(src/devices/CPU)

if(BUILD_TESTS)
    enable_testing() 
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    configure_file(
        "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json"
        "${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json"
        COPYONLY
    )
endif()
