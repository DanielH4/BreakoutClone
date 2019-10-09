#pragma once

#include "Engine/Object.h"
#include "Engine/Vertex.h"
#include "Engine/ResourceManager.h"

#include <vector>

class Face2 : public Engine::Object {
public:
    Face2() 
    : super("../src/res/textures/awesomeface.png", "../src/shaders/shader.vs", "../src/shaders/shader.fs", m_vertices)
    {
        //this->enableAttributes(VERTEX_POSITION_BIT);
    }

    void draw() const {
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

private:
    typedef Engine::Object super;
    float m_vertices[48] = {
        //position          //tex coords
        //first triangle
        0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,       //top right
        0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,      //bottom right
        -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,      //top left

        //second triangle
        0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,      //bottom right
        -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f,     //bottom left
        -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f       //top leftt
    };
};