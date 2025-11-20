cmake_minimum_required(VERSION 3.10)
project(bit_converter C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(bit_converter 
    src/main.c
    src/functions.c
)

target_compile_options(bit_converter PRIVATE -Wall -Wextra -Wpedantic -g)