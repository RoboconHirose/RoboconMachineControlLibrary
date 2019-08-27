cmake_minimum_required(VERSION 3.13)
project(VectorCtrl)

set(CMAKE_CXX_STANDARD 14)

add_executable(VectorCtrl main.cpp VectorCtrl/VectorCtrl.hpp VectorCtrl/VectorCtrl.cpp VectorCtrl/MecanumWheel.cpp VectorCtrl/MecanumWheel.hpp)