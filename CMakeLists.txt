cmake_minimum_required(VERSION 3.13)
project(Ctrl)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ctrl main.cpp Ctrl/Ctrl.hpp Ctrl/VectorCtrl.hpp Ctrl/VectorCtrl.cpp Ctrl/MecanumWheelController.hpp Ctrl/MecanumWheelController.cpp Ctrl/PidController.cpp Ctrl/PidController.hpp)