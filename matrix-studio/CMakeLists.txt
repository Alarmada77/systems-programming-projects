cmake_minimum_required(VERSION 3.30)
project(wet)

set(CMAKE_CXX_STANDARD 17)

add_executable(wet Matrix.cpp Utilities.cpp tests.cpp MataMvidia.cpp)
