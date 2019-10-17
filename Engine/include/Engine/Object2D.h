#pragma once

#include <glm/glm.hpp>

#include "Engine/Texture.h"

#include <string>
#include <cmath>
#include <ctime>

namespace Engine {
    class Object2D {
    public:
        Object2D(const Texture& texture, const glm::vec2 position, const glm::vec2 size, const float degrees);
        virtual void update(int width, int height);
        bool collidesWith(Engine::Object2D& other);
        virtual void handleCollision(Engine::Object2D& other);
        void setVelocity(glm::vec2 velocity);
        void setVelocity(float x, float y);
        void setSize(glm::vec2&& size);
        bool isOutOfBounds() const;
        Engine::Texture getTexture() const;
        glm::vec2 getVelocity() const;
        glm::vec2 getPosition() const;
        glm::vec2 getSize() const;
        float getRotation() const;
        float maxX() const;
        float maxY() const;
        float minX() const;
        float minY() const;
        virtual std::string type() const;

    protected:
        Texture m_texture;
        glm::vec2 m_position;
        glm::vec2 m_size;
        glm::vec2 m_velocity;
        float m_rotation;
        virtual void handleBoundaries();
    };
}