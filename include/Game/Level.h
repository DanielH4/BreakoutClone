#pragma once

#include "Game/Tile.h"
#include "Engine/Object2D.h"

#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <memory>

enum class TileType {
    EMPTY,
    BOX
};

class Level {
public:
    Level(int levelNumber);
    void generate(std::vector<Engine::Object2D*>& gameObjects);

private:
    std::array<std::array<TileType, 15>, 3> m_rows;
};