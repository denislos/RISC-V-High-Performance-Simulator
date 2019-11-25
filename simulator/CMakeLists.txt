cmake_minimum_required(VERSION 3.10)

project(RISC-V-High-Performance-Simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)


set(BOOST_ROOT /p/dpg/arch/perfhome/boost/1.68.0)
set(BOOST_INCLUDE_DIR ${BOOST_ROOT}/include)
set(BOOST_LIB_DIR ${BOOST_ROOT}/gcc9.1/lib64)
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
)


set(SCRIPTS_DIR ${CMAKE_CURRENT_LIST_DIR}/../scripts)
set(RYML_DIR ${CMAKE_CURRENT_LIST_DIR}/../rapidyaml/src)
set(YAMLCPP_DIR ${CMAKE_CURRENT_LIST_DIR}/../yaml-cpp/include)
set(C4CORE_DIR ${CMAKE_CURRENT_LIST_DIR}/../rapidyaml/extern/c4core/src)
set(DEBUGBREAK_DIR ${CMAKE_CURRENT_LIST_DIR}/../rapidyaml/extern/c4core/extern)
set(RISCV_YAML_DEF ${SCRIPTS_DIR}/../simulator/risc-v/risc-v.yaml)
set(RISCV_INSTRS_DEF ${SCRIPTS_DIR}/../simulator/risc-v/risc-v-instructions.def) 
add_custom_command(
    OUTPUT ${RISCV_INSTRS_DEF}
    COMMAND /p/dpg/arch/perfhome/python/miniconda3/bin/python3 ${SCRIPTS_DIR}/generate-riscv-instrs-def.py ${RISCV_YAML_DEF} ${RISCV_INSTRS_DEF}
    DEPENDS ${SCRIPTS_DIR}/generate-riscv-instrs-def.py
)


include_directories(${RYML_DIR} ${C4CORE_DIR} ${DEBUGBREAK_DIR})
include_directories(${YAMLCPP_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/../external ${BOOST_INCLUDE_DIR})
link_directories(${BOOST_LIB_DIR})

add_library(simulator-src-lib STATIC ${SOURCES} ${RISCV_INSTRS_DEF})


add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../rapidyaml ${CMAKE_BINARY_DIR}/rapidyaml)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../yaml-cpp ${CMAKE_BINARY_DIR}/yaml-cpp)

add_executable(simulator top/main.cpp)
target_compile_options(simulator PUBLIC -O3)

target_link_libraries(simulator simulator-src-lib)
target_link_libraries(simulator yaml-cpp)
target_link_libraries(simulator ryml)
target_link_libraries(simulator boost_program_options)
