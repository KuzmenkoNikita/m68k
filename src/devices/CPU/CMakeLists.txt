cmake_minimum_required(VERSION 3.17.0)
project(M68kCPUDevice VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)

set(DECODERS_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/decoders_helpers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ABCD_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ADD_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ADDA_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ADDI_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ADDQ_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ADDX_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/AND_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ANDI_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ANDI_to_CCR_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ANDI_to_SR_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ASL_memory_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ASL_register_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ASR_memory_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ASR_register_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/Bcc_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/BCHG_immediate_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/BCHG_register_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/BCLR_immediate_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/BCLR_register_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/BCLR_register_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/BRA_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/BSET_immediate_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/BSET_register_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/BSR_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/BTST_immediate_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/BTST_register_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/CHK_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/CLR_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/CMP_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/CMPA_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/CMPI_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/CMPM_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/DBcc_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/DIVS_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/DIVU_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/EOR_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/EORI_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/EORI_to_CCR_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/EORI_to_SR_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/EXG_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/EXT_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/JMP_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/JSR_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/LEA_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/LINK_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/LSL_memory_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/LSL_register_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/LSR_memory_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/LSR_register_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/MOVE_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/MOVE_from_SR_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/MOVE_to_CCR_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/MOVE_to_SR_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/MOVE_USP_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/MOVEA_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/MOVEM_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/MOVEP_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/MOVEQ_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/MULS_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/MULU_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/NBCD_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/NEG_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/NEGX_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/NOT_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/OR_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ORI_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ORI_to_CCR_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ORI_to_SR_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/PEA_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ROL_memory_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ROL_register_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ROR_memory_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ROR_register_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ROXL_memory_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ROXL_register_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ROXR_memory_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/ROXR_register_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/SBCD_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/Scc_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/STOP_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/SUB_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/SUBA_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/SUBI_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/SUBQ_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/SUBX_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/SWAP_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/TAS_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/TRAP_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/TST_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/decoders/UNLK_decoder.cpp
)

set(SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cpu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/instruction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/instruction_decoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/instruction_type_decoder.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${DECODERS_SOURCES} ${EXECUTORS_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/cpu/internal)

target_link_libraries(${PROJECT_NAME} PUBLIC BUSMemoryInterface)

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()