cmake_minimum_required(VERSION 2.8)
project(create_window_with_glfw C CXX)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")

add_executable(create_window_with_glfw main.cpp)
target_link_libraries(create_window_with_glfw glfw)