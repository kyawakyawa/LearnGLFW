cmake_minimum_required(VERSION 2.8)
project(initialize_glfw C CXX)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lglfw")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lglfw")

add_executable(initialize_glfw main.cpp)