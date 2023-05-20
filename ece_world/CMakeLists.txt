cmake_minimum_required(VERSION 3.13)
project(ece_world C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-L/usr/local/lib -lalleg")

add_executable(ece_world main.c)
