cmake_minimum_required(VERSION 3.10)

project(RISC-V-High-Performance-Simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -O3")

find_package(Boost REQUIRED)


set(SOURCES
    infra/arg_parse/arg_parser.cpp
    top/main.cpp
    memory/memory.cpp
)


include_directories(${CMAKE_CURRENT_LIST_DIR})


add_library(simulator-src-lib STATIC ${SOURCES})


add_executable(simulator top/main.cpp)
target_link_libraries(simulator simulator-src-lib)
target_link_libraries(simulator boost_program_options)
