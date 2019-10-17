add_library(Engine STATIC
            src/Object2D.cpp
            src/Shader.cpp
            src/SpriteRenderer2D.cpp
            src/Texture.cpp
            src/Window.cpp)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)

target_link_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_link_libraries(
    Engine
    opengl32
    glfw3
    glad
)