cmake_minimum_required(VERSION 3.10)
project(vector C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(vector
    src/main_int.c
    src/vector.c
)

target_compile_options(vector PRIVATE -Wall -Wextra -Wpedantic -g)