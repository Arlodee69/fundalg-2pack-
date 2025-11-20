cmake_minimum_required(VERSION 3.10)
project(brackets C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(brackets
    src/main.c
    src/functions.c
    src/stack.c
)

target_compile_options(brackets PRIVATE -Wall -Wextra -Wpedantic -g)