cmake_minimum_required(VERSION 3.17.0)
project(M68kCPUDevice VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)

set(DECODERS_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/decoders_helpers.cpp
)

set(SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cpu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/instruction_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/instruction_type_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/instruction_factory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/tst_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ORI_to_CCR_decoder.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${DECODERS_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/cpu/internal)

target_link_libraries(${PROJECT_NAME} PUBLIC BUSMemoryInterface)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()