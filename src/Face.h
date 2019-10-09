#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine/Object.h"
#include "Engine/Vertex.h"

#include <vector>

/*
class Object {
public:
    Object(const std::string &texPath, const std::string &vsPath, const std::string &fsPath, float *vertices) 
    : m_texture(Engine::loadTexture(texPath)), m_shader(Engine::createShader(vsPath, fsPath))
    {
        for(int i = 0; i < 48; i++) {
            m_vertices[i] = vertices[i];
        }

        glGenBuffers(1, &m_VBO);
        glGenVertexArrays(1, &m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

        glBindVertexArray(m_VAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    void draw() {
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void useShader() {
        m_shader.use();
    }

    void setShaderInt() {
        m_shader.setInt("uMyTexture", 0);
    }

    void bindVAO() const {
        glBindVertexArray(m_VAO);
    }

    void activateTexture() const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture.getID());
    }

    friend std::ostream& operator<<(std::ostream& stream, const Object& object) {
        for(int i = 0; i < 48; i++) {
            std::cout << object.m_vertices[i] << ", ";
        }

        return stream;
    }

private:
    Engine::Texture m_texture;
    Engine::Shader m_shader;
    unsigned int m_VBO;
    unsigned int m_VAO;
    float m_vertices[48];
};

std::ostream& operator<<(std::ostream& stream, const Object &object);
*/

float glob_vertices[48] = {
        //position          //tex coords
        //first triangle
        0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,       //top right
        0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,      //bottom right
        -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,      //top left

        //second triangle
        0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,      //bottom right
        -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f,     //bottom left
        -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f       //top left
};

class Face : public Engine::Object {
public:
    Face() 
    : super("../src/res/textures/awesomeface.png", "../src/shaders/shader.vs", "../src/shaders/shader.fs", 
        std::vector<Vertex> {
            Vertex(0.5f, 0.5f, 0.0f, 1.0f, 1.0f),
            Vertex(0.5f, -0.5f, 0.0f, 1.0f, 0.0f),
            Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 1.0f),
            Vertex(0.5f, -0.5f, 0.0f, 1.0f, 0.0f),
            Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f), 
            Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 1.0f)
        })
    {
        super::enableAttributes(VERTEX_POSITION_BIT | VERTEX_TEXCOORD_BIT);
        super::setShaderInt("uMyTexture", 0);
    }

private:
    typedef Engine::Object super;
    typedef Engine::Vertex Vertex;
};

/*
class Face {
public:
    Face() 
    : m_tex(Engine::loadTexture("../src/res/textures/awesomeface.png")), m_shader(Engine::createShader("../src/shaders/shader.vs", "../src/shaders/shader.fs"))
    {
        glGenBuffers(1, &m_VBO);
        glGenVertexArrays(1, &m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(m_VAO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    void draw() const {
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void useShader() const {
        m_shader.use();
    }

    void setShaderInt() {
        m_shader.setInt("uMyTexture", 0);
    }

    void bindVAO() const {
        glBindVertexArray(m_VAO);
    }

    void activateTexture() const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_tex.getID());
    }

private:
    Engine::Texture m_tex;
    Engine::Shader m_shader;
    unsigned int m_VBO;
    unsigned int m_VAO;
    float vertices[48] = {
        //position          //tex coords
        //first triangle
        0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,       //top right
        0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,      //bottom right
        -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,      //top left

        //second triangle
        0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,      //bottom right
        -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f,     //bottom left
        -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f       //top left
    };
};
*/