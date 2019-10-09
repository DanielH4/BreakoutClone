#pragma once

#include <glm/glm.hpp>

#include "Engine/Texture.h"

#include <iostream>

namespace Engine {
    class Object2D {
    public:
        Object2D(const Texture& texture, const glm::vec2 position, const glm::vec2 size, const float degrees)
        : m_texture(texture), m_position(position), m_size(size), m_rotation(degrees), m_velocity(glm::vec2{0, 0}) 
        {
        }

        void update(int width, int height) {
            if(m_position.x > maxX(width) || m_position.x < minX())
                m_velocity.x = -m_velocity.x;
            if(m_position.y > maxY(height) || m_position.y < minY())
                m_velocity.y = -m_velocity.y;
            m_position += m_velocity;
            //m_position.x += glfwGetTime() * 0.3;
        }

        Engine::Texture getTexture() const {
            return m_texture;
        }

        constexpr glm::vec2 getPosition() const {
            return m_position;
        }

        constexpr glm::vec2 getSize() const {
            return m_size;
        }

        constexpr float getRotation() const {
            return m_rotation;
        }

        constexpr int maxX(int width) const {
            return (width - m_position.x);
        }

        constexpr int maxY(int height) const {
            return (height - m_position.y);
        }

        constexpr int minX() const {
            return m_position.x;
        }

        constexpr int minY() const {
            return m_position.y;
        }

    private:
        Texture m_texture;
        glm::vec2 m_position;
        glm::vec2 m_size;
        glm::vec2 m_velocity;
        float m_rotation;
    };
}