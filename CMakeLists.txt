cmake_minimum_required(VERSION 3.23)
project(Taupesv3 C)

set(CMAKE_C_STANDARD 99)

add_executable(Taupesv3 main.c)

target_link_libraries(Taupesv3 -lmingw32 -lalleg44)
