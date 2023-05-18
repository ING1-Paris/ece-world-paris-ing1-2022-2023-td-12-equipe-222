cmake_minimum_required(VERSION 3.23)
project(ECE_WORLD17 C)

set(CMAKE_C_STANDARD 99)

add_executable(ECE_WORLD17 main.c)

target_link_libraries(ECE_WORLD17 -lmingw32 -lalleg44)