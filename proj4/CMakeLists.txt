cmake_minimum_required(VERSION 3.10.0)
project(proj4test VERSION 0.1.0 LANGUAGES C CXX)

add_executable(proj4test test.cpp)

include(CTest)
enable_testing()
