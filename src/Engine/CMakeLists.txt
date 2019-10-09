cmake_minimum_required(VERSION 3.0)

project(Engine)

find_package(OpenGL REQUIRED)

add_library(Engine STATIC main.cpp)

target_link_libraries(
    Engine
    opengl32
    glfw3
    glad
)