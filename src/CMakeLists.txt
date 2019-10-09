add_subdirectory(Engine)

link_directories(Engine/lib)

add_executable(Game main.cpp)

target_link_libraries(Game Engine)