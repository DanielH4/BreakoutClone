cmake_minimum_required(VERSION 3.0)

Project(BreakoutClone)

include_directories(
    include
    Engine/include
)

add_subdirectory(Engine)
add_subdirectory(src)