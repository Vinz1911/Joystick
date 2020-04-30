cmake_minimum_required(VERSION 3.16)
project(Dynamixel_XL430)
include_directories(/usr/local/include)

set(CMAKE_CXX_STANDARD 17)

add_executable(Joystick++ main.cpp)