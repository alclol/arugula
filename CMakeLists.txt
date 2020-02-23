cmake_minimum_required(VERSION 3.14)
project(arugula 
        VERSION 1.0.0 
        DESCRIPTION "a c++ lattice library for program monotonicity check")

set(CMAKE_CXX_STANDARD 17)
Set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DCATCH_CONFIG_ENABLE_BENCHMARKING ")

add_library(arugula_lib INTERFACE)
target_include_directories(arugula_lib INTERFACE include/)
target_include_directories(arugula_lib INTERFACE include/merges)
target_include_directories(arugula_lib INTERFACE include/utils)

add_subdirectory(test)


