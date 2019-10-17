#include "Game/Player.h"

Player::Player(Engine::Texture&& texture, glm::vec2&& position, glm::vec2&& size, GLFWwindow* glfwWindow) 
: super(std::move(texture), std::move(position), std::move(size), 45.0f), m_glfwWindow(glfwWindow), m_speed(500.0f), m_effect(Powerup::Effect::NONE) {}

void Player::update(int width, int height) {
    handleBoundaries();
    m_position += m_velocity;
    if(m_effect != Powerup::Effect::NONE) {
        if(((clock() - m_powerupTimer) / CLOCKS_PER_SEC) > 10.0f) {
            removePowerup();
        }
    }
}

void Player::processInput(float deltatime) {
    float velocity = m_speed * deltatime;
    if((glfwGetKey(m_glfwWindow, GLFW_KEY_D) || glfwGetKey(m_glfwWindow, GLFW_KEY_RIGHT)) == GLFW_PRESS) {
        if(m_position.x < maxX()) {
            m_position.x += velocity;
        }
    }
    if((glfwGetKey(m_glfwWindow, GLFW_KEY_A) || glfwGetKey(m_glfwWindow, GLFW_KEY_LEFT)) == GLFW_PRESS) {
        if(m_position.x > minX()) {
            m_position.x -= velocity;
        }
    }
}

void Player::addPowerup(Powerup::Effect effect) {
    if(m_effect == Powerup::Effect::NONE) {
        m_effect = effect;
        if(m_effect == Powerup::Effect::ENLARGE) {
            m_size.x *= 1.5f;
        }
        else if(m_effect == Powerup::Effect::SPEEDUP) {
            m_speed *= 2.0f;
        }
        m_powerupTimer = clock();
    }
}

//handle collisions with ball
void Player::handleCollision(Engine::Object2D& other) {
    glm::vec2 otherPos = other.getPosition();
    glm::vec2 otherSize = other.getSize();
    glm::vec2 otherVel = other.getVelocity();
    if((otherPos.y + otherSize.y) < m_position.y)
        otherVel.y = -otherVel.y;
    other.setVelocity(otherVel);
}

void Player::removePowerup() {
    if(m_effect == Powerup::Effect::ENLARGE) {
        m_size.x = 0.66f * m_size.x;
    }
    else if(m_effect == Powerup::Effect::SPEEDUP) {
        m_speed = m_speed / 2;
    }
    m_effect = Powerup::Effect::NONE;
}

std::string Player::type() const {
    return "Player";
}

