cmake_minimum_required(VERSION 3.17)
project(linkBase VERSION 0.2.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

add_executable(linkBase main.c linkedList.c linkedList.h)
add_executable(test test.c linkedList.c linkedList.h)
