#include "Engine/Window.h"

namespace Engine {
    //resizing of window
    void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    Window::Window(const int width, const int height, const std::string title)
    : m_width(width), m_height(height), m_title(title)
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

    Window::~Window() {
        glfwDestroyWindow(m_GLFWwindow);
    }

    //returns reference to GLFWwindow object
    GLFWwindow& Window::getWindowGLFW() {
        return *m_GLFWwindow;
    }

    int Window::getWidth() const {
        return m_width;
    }

    int Window::getHeight() const {
        return m_height;
    }

    void Window::processInput(float deltaTime) {
        if(glfwGetKey(m_GLFWwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_GLFWwindow, true);
    }

    void Window::mouseCallback(double xpos, double ypos) {
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
    }

    void Window::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
        Window *myWin = static_cast<Window*>(glfwGetWindowUserPointer(window));
        myWin->mouseCallback(xpos, ypos);
    }
}