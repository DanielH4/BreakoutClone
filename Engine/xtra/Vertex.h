#pragma once

namespace Engine {
    struct Vertex {
        Vertex( float x, float y, float z,
                float red, float green, float blue,
                float xTex, float yTex) 
        : x(x), y(y), z(z), red(red), green(green), blue(blue), xTex(xTex), yTex(yTex)
        {
        }

        Vertex(float x, float y, float z)
        : x(x), y(y), z(z)
        {
        }
    
        Vertex(float x, float y, float z, float xTex, float yTex)
        : x(x), y(y), z(z), xTex(xTex), yTex(yTex)
        {
        }

        float x, y, z;
        float red, green, blue;
        float xTex, yTex;
    };
}