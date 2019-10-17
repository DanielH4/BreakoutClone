#include "Game/Powerup.h"

Powerup::Powerup(Effect effect, Engine::Texture&& texture, glm::vec2&& position, glm::vec2&& size, glm::vec2&& velocity) 
: super(std::move(texture), std::move(position), std::move(size), 0.0f), m_effect(effect)
{
    this->setVelocity(velocity);
}

Powerup::Effect Powerup::getEffect() const {
    return m_effect;
}

std::string Powerup::type() const {
    return "Powerup";
}

void Powerup::handleBoundaries() {
    if(m_position.x > maxX() || m_position.x < minX())
        m_velocity.x = -m_velocity.x;
    if(m_position.y < minY())
        m_velocity.y = -m_velocity.y;
}