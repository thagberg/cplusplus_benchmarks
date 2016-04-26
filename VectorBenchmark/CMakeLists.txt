cmake_minimum_required(VERSION 3.3)
project(VectorBenchmark)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-elide-constructors")

set(SOURCE_FILES main.cpp)
add_executable(VectorBenchmark ${SOURCE_FILES})