cmake_minimum_required(VERSION 2.8)
project(do_not_close_window C CXX) # Project Name
set(CMAKE_CXX_STANDARD 17) # -std=c++17

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall") # C option 
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall") # CXX option

add_executable(do_not_close_window main.cpp) # binary_name source source ...
target_link_libraries(do_not_close_window glfw GL) # Link Libraries
