cmake_minimum_required(VERSION 3.23)
project(TAUPES C)

set(CMAKE_C_STANDARD 99)

add_executable(TAUPES main.c)

target_link_libraries(TAUPES -lmingw32 -lalleg44)