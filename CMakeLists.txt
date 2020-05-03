cmake_minimum_required(VERSION 3.13)
project(PSGamepad)
link_libraries(-lpthread)

set(CMAKE_CXX_STANDARD 17)

add_executable(GamepadDemo main.cpp)