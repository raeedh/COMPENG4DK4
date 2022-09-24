cmake_minimum_required(VERSION 3.23)
project(4DK4 C)

set(CMAKE_C_STANDARD 11)

include_directories("Lab 1/code")

add_compile_options(-O3 -march=native)

add_executable(4DK4
        "Lab 1/code/coe4dk4_lab_1_2022_exp8.c"
        "Lab 1/code/simlib.c"
        "Lab 1/code/simlib.h"
        "Lab 1/code/trace.h")
