#pragma once

#include <glm/glm.hpp>

#include "Engine/Object2D.h"
#include "Engine/Texture.h"

class Tile : public Engine::Object2D {
public:
    Tile(Engine::Texture&& texture, glm::vec2&& position, glm::vec2&& size);
    std::string type() const override;

private:
    typedef Engine::Object2D super;
};