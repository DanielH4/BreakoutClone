cmake_minimum_required(VERSION 3.0)

project(GameEngine)

include_directories(
    src/Engine
    src/Engine/include
    src
)

add_subdirectory(src)