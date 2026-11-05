cmake_minimum_required(VERSION 3.10.0)
project(learn-opengl VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(external)

add_executable(learn-opengl main.cpp)
target_link_libraries(learn-opengl glfw glad)
