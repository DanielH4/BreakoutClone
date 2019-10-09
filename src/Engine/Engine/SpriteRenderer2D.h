#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/Shader.h"
#include "Engine/Texture.h"
#include "Engine/Object2D.h"

#include <iostream>

namespace Engine {
    class SpriteRenderer2D {
    public:
        SpriteRenderer2D(Shader &&shader) 
        : m_shader(shader)  
        {
            GLuint VBO;
            GLfloat vertices[] = {
                -1.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 1.0f, 0.0f,

                -1.0f, 1.0f, 0.0f, 1.0f, 
                -1.0f, -1.0f, 0.0f, 0.0f,
                1.0f, -1.0f, 1.0f, 0.0f
            };

            glGenBuffers(1, &VBO);
            glGenVertexArrays(1, &m_VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindVertexArray(m_VAO);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(0));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
            glEnableVertexAttribArray(1);
        }

        ~SpriteRenderer2D() {
            glDeleteVertexArrays(1, &m_VAO);
        }

        void draw(const Object2D& object) {
            object.getTexture().bind();

            //set uniforms
            m_shader.use();
            m_shader.setInt("uMyTexture", 0);
            //implement position, size, rotation translation/scaling etc. add necessary logic to shaders. 
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(object.getPosition(), 0.0f));  
            //model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
            model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)); 
            //model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

            model = glm::scale(model, glm::vec3(object.getSize(), 1.0f)); ;
            m_shader.setMat4("uModel", model);

            glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
            m_shader.setMat4("uProjection", projection);

            glBindVertexArray(m_VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }

    private:
        Shader m_shader;
        GLuint m_VAO;
    };
}