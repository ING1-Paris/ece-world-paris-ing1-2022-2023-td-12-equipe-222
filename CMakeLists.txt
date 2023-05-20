cmake_minimum_required(VERSION 3.23)
project(projetAllegro_carte C)

set(CMAKE_C_STANDARD 23)

add_executable(projetAllegro_carte main.c)

target_link_libraries(projetAllegro_carte -lmingw32 -lalleg44)
