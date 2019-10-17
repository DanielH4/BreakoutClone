#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
    enum class Direction {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    //default values
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 3.5f;
    const float SENSITIVITY = 0.05f;

    class Camera {
    public:
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        glm::vec3 cameraRight;
        float yaw;
        float pitch;
        float movementSpeed;
        float sensitivity;

        Camera( glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f), 
                glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f), 
                glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f), 
                float yaw = YAW, float pitch = PITCH, float movementSpeed = SPEED, float sensitivity = SENSITIVITY) 
        {
            this->cameraPos = cameraPos;
            this->cameraFront = cameraFront;
            this->cameraUp = cameraUp;
            this->cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
            this->yaw = yaw;
            this->pitch = pitch;
            this->movementSpeed = movementSpeed;
            this->sensitivity = sensitivity;

            updateCameraVectors();
        }

        glm::mat4 getViewMatrix() {
            return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        }

        void processKeyboardInput(Direction dir, float deltatime) {
            float velocity = movementSpeed * deltatime;
            if(dir == Direction::FORWARD)
                cameraPos += cameraFront * velocity;
            if(dir == Direction::BACKWARD)
                cameraPos -= cameraFront * velocity;
            if(dir == Direction::LEFT)
                cameraPos -= cameraRight * velocity;
            if(dir == Direction::RIGHT)
                cameraPos += cameraRight * velocity;
            
        }

        void processMouseInput(float xoffset, float yoffset) {
            xoffset *= sensitivity;
            yoffset *= sensitivity;

            yaw -= xoffset;
            pitch += yoffset;

            if(pitch > 89.0f)
                pitch = 89.0f;
            if(pitch < -89.0f)
                pitch = -89.0f;

            updateCameraVectors();
        }

    private:
        void updateCameraVectors() {
            cameraFront.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
            cameraFront.y = sin(glm::radians(pitch));
            cameraFront.z = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
            glm::normalize(cameraFront);
            cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
        }
    };
}