cmake_minimum_required(VERSION 3.13)
project(PSGamepad)
link_libraries(-lpthread)

set(CMAKE_CXX_STANDARD 17)

add_executable(GamepadDemo main.cpp ps_gamepad.cpp)
install(FILES ps_gamepad.h ps_gamepad.cpp ps_gamepad_keys.cpp DESTINATION /usr/local/include/PSGamepad)