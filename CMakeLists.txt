cmake_minimum_required(VERSION 3.17.0)
project(m68k VERSION 0.1.0 LANGUAGES C CXX)

add_executable(m68k main.cpp)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
