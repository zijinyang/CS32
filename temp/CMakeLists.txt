cmake_minimum_required(VERSION 3.10.0)
project(temp VERSION 0.1.0 LANGUAGES C CXX)

add_executable(temp bs.cpp)

include(CTest)
enable_testing()

