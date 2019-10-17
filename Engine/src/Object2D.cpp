#include "Engine/Object2D.h"

namespace Engine {
    Object2D::Object2D(const Texture& texture, const glm::vec2 position, const glm::vec2 size, const float degrees)
    : m_texture(texture), m_position(position), m_size(size), m_rotation(degrees), m_velocity(glm::vec2{0, 0}) 
    {
    }

    void Object2D::update(int width, int height) {
        handleBoundaries();
        m_position += m_velocity;
    }

    void Object2D::setVelocity(glm::vec2 velocity) {
        m_velocity = velocity;
    }

    void Object2D::setVelocity(float x, float y) {
        m_velocity.x = x;
        m_velocity.y = y;
    }

    void Object2D::setSize(glm::vec2&& size) {
        m_size = size;
    }

    Texture Object2D::getTexture() const {
        return m_texture;
    }

    glm::vec2 Object2D::getVelocity() const {
        return m_velocity;
    }

    glm::vec2 Object2D::getPosition() const {
        return m_position;
    }

    glm::vec2 Object2D::getSize() const {
        return m_size;
    }

    float Object2D::getRotation() const {
        return m_rotation;
    }

    bool Object2D::collidesWith(Engine::Object2D& other) {
        const glm::vec2& thisPos = m_position;
        const glm::vec2& thisSize = m_size;
        float thisMinX = thisPos.x - thisSize.x;
        float thisMinY = thisPos.y - thisSize.y;
        float thisMaxX = thisPos.x + thisSize.x;
        float thisMaxY = thisPos.y + thisSize.y;

        const glm::vec2& otherPos = other.m_position;
        const glm::vec2& otherSize = other.m_size;
        float otherMinX = otherPos.x - otherSize.x;
        float otherMinY = otherPos.y - otherSize.y;
        float otherMaxX = otherPos.x + otherSize.x;
        float otherMaxY = otherPos.y + otherSize.y;

        bool xCollision = thisMaxX > otherMinX && otherMaxX > thisMinX;
        bool yCollision = thisMaxY > otherMinY && otherMaxY > thisMinY;

        return xCollision && yCollision;
    }

    void Object2D::handleCollision(Engine::Object2D& other) {
        /*
        glm::vec2 otherToThis = otherPos - thisPos;
        glm::vec2 xDir(1, 0);
        float angle = glm::acos(glm::dot(otherToThis, xDir) / (glm::length(otherToThis) * glm::length(xDir)));
        //std::cout << glm::degrees(2*angle) << " => change in ";
        if(angle >= 2.355 || angle <= 0.785) {
            std::cout << "x direction" << std::endl;
            m_velocity.x = -m_velocity.x;
        }
        else {
            std::cout << "y direction" << std::endl;
            m_velocity.y = -m_velocity.y;
        }
        */

        //if there is a collision in the x and y axis, the x or y axis is reverted based on what axis collided last.
        if(std::abs(m_position.x - other.m_position.x) > std::abs(m_position.y - other.m_position.y)) {
            m_velocity.x = -m_velocity.x;
        }
        else {
            m_velocity.y = -m_velocity.y;
        }
    }

    void Object2D::handleBoundaries() {
        if(m_position.x > maxX() || m_position.x < minX())
            m_velocity.x = -m_velocity.x;
        if(m_position.y < minY())
            m_velocity.y = -m_velocity.y;        
    }

    bool Object2D::isOutOfBounds() const {
        if((m_position.y - m_size.y) > maxY())
            return true;
        return false;
    }

    float Object2D::maxX() const {
        return (800 - m_size.x);
    }

    float Object2D::maxY() const {
        return (600 - m_size.y);
    }

    float Object2D::minX() const {
        return m_size.x;
    }

    float Object2D::minY() const {
        return m_size.y;
    }

    std::string Object2D::type() const {
        return "Object2D";
    }
}