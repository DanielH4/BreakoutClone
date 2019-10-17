#pragma once

#include <glm/glm.hpp>

#include "Engine/Texture.h"
#include "Engine/Object2D.h"
#include "Game/Powerup.h"

#include <time.h>
#include <memory>

class Powerup;
class Player : public Engine::Object2D {
public:
    Player(Engine::Texture&& texture, glm::vec2&& position, glm::vec2&& size, GLFWwindow* glfwWindow);
    void update(int width, int height) override;
    void processInput(float deltatime);
    void addPowerup(Powerup::Effect effect);
    void handleCollision(Engine::Object2D& other) override;     //handle player collision with ball
    std::string type() const override;

private:
    typedef Engine::Object2D super;
    float m_speed;
    Powerup::Effect m_effect;
    clock_t m_powerupTimer;
    GLFWwindow* m_glfwWindow;           //keeps track of what glfw window the player belongs to 
    void removePowerup();
};