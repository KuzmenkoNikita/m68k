cmake_minimum_required(VERSION 3.17.0)
project(M68kCPUDevice VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)

set(DECODERS_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/decoders_helpers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/TST_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ORI_to_CCR_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ORI_decoder.cpp
)

set(EXECUTORS_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/executors/TST_executor.cpp
)

set(SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cpu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/instruction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/instruction_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/instruction_type_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/instruction_factory.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${DECODERS_SOURCES} ${EXECUTORS_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/cpu/internal)

target_link_libraries(${PROJECT_NAME} PUBLIC BUSMemoryInterface)

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()