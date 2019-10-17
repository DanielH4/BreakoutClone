#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/Shader.h"
//#include "Engine/Texture.h"
#include "Engine/Object2D.h"

class Texture;

namespace Engine {
    class SpriteRenderer2D {
    public:
        SpriteRenderer2D(Shader&& shader);
        ~SpriteRenderer2D();
        void draw(const Object2D& object);

    private:
        Shader m_shader;
        GLuint m_VAO;
    };
}