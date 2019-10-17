#include "Game/Tile.h"

Tile::Tile(Engine::Texture&& texture, glm::vec2&& position, glm::vec2&& size) 
: super(texture, std::move(position), std::move(size), 0.0f)
{
}

std::string Tile::type() const {
    return "Tile";
}