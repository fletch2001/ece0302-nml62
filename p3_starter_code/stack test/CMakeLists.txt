cmake_minimum_required(VERSION 3.5)
project(P2 CXX)

#require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(SOURCE stack_tests.cpp Stack.hpp Stack.cpp)

add_executable(stack-test stack_tests.cpp)

enable_testing()