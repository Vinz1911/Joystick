cmake_minimum_required(VERSION 3.13)
project(PSGamepad)
link_libraries(-lpthread)

set(CMAKE_CXX_STANDARD 17)

add_executable(GamepadDemo example/main.cpp)
install(FILES src/ps_gamepad.h src/ps_gamepad.cpp src/ps_gamepad_keys.cpp DESTINATION /usr/local/include/PSGamepad)