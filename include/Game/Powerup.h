#pragma once

#include <glm/glm.hpp>

#include "Engine/Object2D.h"
#include "Engine/Texture.h"

class Powerup : public Engine::Object2D {
public:
    enum class Effect {
        NONE,
        ENLARGE,
        SPEEDUP
    };

    Powerup(Effect effect, Engine::Texture&& texture, glm::vec2&& position, glm::vec2&& size, glm::vec2&& velocity = glm::vec2(0.0f));
    Effect getEffect() const;
    std::string type() const override;

protected:
    void handleBoundaries() override;

private:
    typedef Engine::Object2D super;
    Effect m_effect;
};