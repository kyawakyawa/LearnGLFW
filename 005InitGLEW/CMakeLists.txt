cmake_minimum_required(VERSION 2.8)
project(terminate_process C CXX) # Project Name
set(CMAKE_CXX_STANDARD 17) # -std=c++17

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall") # C option 
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall") # CXX option

add_executable(init_glew main.cpp) # binary_name source source ...
target_link_libraries(init_glew GLEW glfw GL) # Link Libraries
