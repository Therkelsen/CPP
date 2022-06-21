cmake_minimum_required(VERSION 3.21)
project(NUM_Utils)

set(CMAKE_CXX_STANDARD 23)

include_directories(../Assets/NR_C301/code/)

add_executable(NUM_Utils main.cpp NM_Utils.h test.h)
