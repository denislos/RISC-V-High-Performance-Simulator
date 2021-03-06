cmake_minimum_required(VERSION 3.10)

project(RISC-V-High-Performance-Simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)



find_package(Boost REQUIRED)


set(SOURCES
    top/main.cpp
    top/simulator.cpp
    kernel/kernel.cpp
    infra/config/config.cpp
    memory/memory.cpp
    memory/elf/elf_loader.cpp
    top/base_instruction.cpp
    infra/decoder/decode_tree.cpp
    executor/executor.cpp
    functional/funcsim.cpp
    functional/rf/rf.cpp
    functional/fetch/fetch.cpp
    functional/func_memory.cpp
)


set(SCRIPTS_DIR ${CMAKE_CURRENT_LIST_DIR}/../scripts)
set(YAMLCPP_DIR ${CMAKE_CURRENT_LIST_DIR}/../yaml-cpp/include)

set(RISCV_YAML_DEF ${SCRIPTS_DIR}/../simulator/risc-v/risc-v.yaml)
set(RISCV_INSTRS_DEF ${SCRIPTS_DIR}/../simulator/risc-v/risc-v-instructions.def) 
add_custom_command(
    OUTPUT ${RISCV_INSTRS_DEF}
    COMMAND python3 ${SCRIPTS_DIR}/generate-riscv-instrs-def.py ${RISCV_YAML_DEF} ${RISCV_INSTRS_DEF}
    DEPENDS ${SCRIPTS_DIR}/generate-riscv-instrs-def.py
)


set(YAMLCPP_DIR ${CMAKE_CURRENT_LIST_DIR}/../yaml-cpp/include)
include_directories(${YAMLCPP_DIR})

include_directories(${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/../external ${BOOST_INCLUDE_DIR})

add_library(simulator-src-lib STATIC ${SOURCES} ${RISCV_INSTRS_DEF})


add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../yaml-cpp ${CMAKE_BINARY_DIR}/yaml-cpp)

add_executable(simulator top/main.cpp)
target_compile_options(simulator PUBLIC -Wall -Werror -Wextra -O3)

target_link_libraries(simulator simulator-src-lib)
target_link_libraries(simulator yaml-cpp)
target_link_libraries(simulator boost_program_options)
