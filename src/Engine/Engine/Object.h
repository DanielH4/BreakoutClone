#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine/Texture.h"
#include "Engine/Shader.h"
#include "Engine/Vertex.h"

#include <vector>
#include <string>
#include <bitset>

#define VERTEX_POSITION_BIT     1
#define VERTEX_COLOR_BIT        2
#define VERTEX_TEXCOORD_BIT     4

namespace Engine {
    class Object {
    public:
        Object(const std::string &texPath, const std::string &vsPath, const std::string &fsPath, std::vector<Vertex> vertices) 
        : m_texture(Texture(texPath)), m_shader(Shader(vsPath.c_str(), fsPath.c_str())), m_vertices(vertices)
        {
            glGenBuffers(1, &m_VBO);
            glGenVertexArrays(1, &m_VAO);

            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &m_vertices.front(), GL_STATIC_DRAW);
        }

        void enableAttributes(unsigned char attributes) {
            glBindVertexArray(m_VAO);
            if(attributes & VERTEX_POSITION_BIT) {
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
                glEnableVertexAttribArray(0);
            }
            if(attributes & VERTEX_COLOR_BIT) {
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
                glEnableVertexAttribArray(1);
            }
            if(attributes & VERTEX_TEXCOORD_BIT) {
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
                glEnableVertexAttribArray(2);
            }
        }

        virtual void draw() const {
            glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
        }

        void useShader() {
            m_shader.use();
        }

        void bindVAO() const {
            glBindVertexArray(m_VAO);
        }

        void activateTexture() const {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_texture.getID());
        }

    protected:
        Engine::Texture m_texture;
        Engine::Shader m_shader;
        std::vector<Vertex> m_vertices;
        unsigned int m_VBO;
        unsigned int m_VAO;

        void setShaderInt(const std::string &name, const int &pos) {
            m_shader.setInt(name, pos);
        }
    };
}