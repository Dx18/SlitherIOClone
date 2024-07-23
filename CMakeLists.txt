
# You are free to modify this file

cmake_minimum_required(VERSION 3.0)
project(game)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(X11 REQUIRED)
set(CMAKE_CONFIGURATION_TYPES "Debug" "Release")
file(GLOB SRC *.cpp)
add_executable(game ${SRC})
target_link_libraries(game m X11)
