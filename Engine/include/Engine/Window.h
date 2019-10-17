#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

namespace Engine {
    class Window {
    public:
        Window(const int width, const int height, const std::string title);
        ~Window(); 
        //returns reference to GLFWwindow object
        GLFWwindow& getWindowGLFW();
        int getWidth() const;
        int getHeight() const;
        void processInput(float deltaTime);
        void mouseCallback(double xpos, double ypos);

    private:
        GLFWwindow *m_GLFWwindow;
        int m_width;
        int m_height;
        const std::string m_title;
        static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    };
}