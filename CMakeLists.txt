cmake_minimum_required(VERSION 3.23)
project(4DK4 C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-O3 -march=native)

file(GLOB LAB1 "Lab 1/code/simlib/*" "Lab 1/code/coe4dk4_lab_1_2022.c")
file(GLOB LAB2 "Lab 2/code/*.h" "Lab 2/code/*.c")

add_executable(${PROJECT_NAME} ${LAB2})
