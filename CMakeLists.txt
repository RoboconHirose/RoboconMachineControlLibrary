cmake_minimum_required(VERSION 3.13)
project(VectorCtrl)

set(CMAKE_CXX_STANDARD 14)

add_executable(VectorCtrl main.cpp src/VectorCtrl.hpp src/VectorCtrl.cpp)