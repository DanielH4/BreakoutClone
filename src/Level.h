#pragma once

#include "Engine/Object2D.h"
#include "Engine/ResourceManager.h"

#include <vector>
#include <bitset>

enum class Tile {
    BOX
};

class Game;
class Level {
public:
    Level(std::bitset<8> rows) 
    : m_rows(rows)
    {
    }

    void generate(std::vector<Engine::Object2D>& gameObjects, int windowWidth, int windowHeight) {
        /*
        gameObjects.push_back(Engine::Object2D{Engine::loadTexture("../src/res/textures/container.jpg"),
                                                glm::vec2{200, 200},
                                                glm::vec2{100, 100},
                                                0.0f});
        */
        for(int i = 0; i < 8; i++) {
            if(m_rows.test(i) == true) {
                gameObjects.push_back(Engine::Object2D{Engine::loadTexture("../src/res/textures/container.jpg"),
                                                        glm::vec2{50+(i*100), 50},
                                                        glm::vec2{50, 50},
                                                        0.0f});
            }
        }
    }

private:
    std::bitset<8> m_rows;
};