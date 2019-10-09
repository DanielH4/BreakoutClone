#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "Engine/Camera.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

namespace Engine {
    class Window {
    public:
        Window(const int width, const int height, const std::string title) 
            :   m_width(width), m_height(height), m_title(title)
        {
            //initialize glfw
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            m_GLFWwindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
            if(m_GLFWwindow == nullptr) {
                std::cout << "Failed to create GLFW window." << std::endl;
                glfwTerminate();
            }
            glfwMakeContextCurrent(m_GLFWwindow);
            glfwSetWindowUserPointer(m_GLFWwindow, this);
            glfwSetFramebufferSizeCallback(m_GLFWwindow, framebufferSizeCallback);
            //glfwSetInputMode(m_GLFWwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(m_GLFWwindow, mouseCallback);

            //initialize glad
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cout << "Failed to initialize GLAD" << std::endl;
            }
        }

        ~Window() {
            glfwDestroyWindow(m_GLFWwindow);
        }

        //returns pointer to GLFWwindow object
        constexpr GLFWwindow& getWindowGLFW() const {
            return *m_GLFWwindow;
        }

        constexpr int getWidth() const {
            return m_width;
        }

        constexpr int getHeight() const {
            return m_height;
        }

        constexpr Camera* getCamera() {
            return &m_camera;
        }

        //attach camera object to window. 
        void setCamera(Camera camera) {
            m_camera = camera;
        }

        void processInput(float deltaTime) {
            if(glfwGetKey(m_GLFWwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(m_GLFWwindow, true);
            if(glfwGetKey(m_GLFWwindow, GLFW_KEY_W) == GLFW_PRESS)
                m_camera.processKeyboardInput(Direction::FORWARD, deltaTime);
            if(glfwGetKey(m_GLFWwindow, GLFW_KEY_S) == GLFW_PRESS)
                m_camera.processKeyboardInput(Direction::BACKWARD, deltaTime);
            if(glfwGetKey(m_GLFWwindow, GLFW_KEY_A) == GLFW_PRESS)
                m_camera.processKeyboardInput(Direction::LEFT, deltaTime);
            if(glfwGetKey(m_GLFWwindow, GLFW_KEY_D) == GLFW_PRESS)
                m_camera.processKeyboardInput(Direction::RIGHT, deltaTime);
        }

    private:
        GLFWwindow *m_GLFWwindow;
        Camera m_camera;
        int m_width;
        int m_height;
        const std::string m_title;

        void mouseCallback(double xpos, double ypos) {
            static bool s_firstMouse = true;
            static float s_yaw = -90.0f;
            static float s_pitch = 0.0f;
            static float s_lastX = m_width / 2;
            static float s_lastY = m_height / 2;

            if(s_firstMouse) {
                s_lastX = xpos;
                s_lastY = ypos;
                s_firstMouse = false;
            }

            float xoffset, yoffset;
            xoffset = xpos - s_lastX;
            yoffset = s_lastY - ypos;
            s_lastX = xpos;
            s_lastY = ypos;

            if(&m_camera)
                m_camera.processMouseInput(xoffset, yoffset);
        }

        /*
        void framebufferSizeCallback(int width, int height) {
            m_width = width;
            m_height = height;
            glViewport(0, 0, width, height);
        }
        */

        static void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
            Window *myWin = static_cast<Window*>(glfwGetWindowUserPointer(window));
            myWin->mouseCallback(xpos, ypos);
        }

        /*
        static void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
            Window *myWin = static_cast<Window*>(glfwGetWindowUserPointer(window));
            myWin->framebufferSizeCallback(width, height);
        }
        */
    };
}