cmake_minimum_required(VERSION 3.21)
project(Learning)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(containers INTERFACE)

target_include_directories(containers INTERFACE
        include/containers include/interfaces
)
target_compile_options(containers INTERFACE -Wall -Wextra -pedantic -Werror)

add_executable(Learning main.cpp)

target_link_libraries(Learning containers)
