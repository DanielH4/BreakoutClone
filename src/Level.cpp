#include "Game/Level.h"

Level::Level(int levelNumber) {
    std::ifstream inFile("../levels/level" + std::to_string(levelNumber) + ".txt");
    std::string inString;
    for(int i = 0; i < m_rows.size(); i++) {
        for(int j = 0; j < m_rows.at(i).size(); j++) {
            inFile >> inString;
            if(inString == "1") {
                m_rows[i][j] = TileType::BOX;
            }
            else {
                m_rows[i][j] = TileType::EMPTY;
            }
        }
        inString.clear();
    }
    inFile.close();
}

void Level::generate(std::vector<Engine::Object2D*>& gameObjects) {
    int tileSize = 25;
    int xPosPtr = tileSize;     //initial x position
    int yPosPtr = tileSize;     //initial y position
    for(int i = 0; i < m_rows.size(); i++) {
        for(int j = 0; j < m_rows.at(i).size(); j++) {
            if(m_rows[i][j] == TileType::BOX) {
                gameObjects.push_back(new Tile(Engine::Texture("../res/textures/container.jpg"),
                                                glm::vec2{xPosPtr, yPosPtr},
                                                glm::vec2{tileSize, tileSize}));
            }
            xPosPtr += (tileSize*2) + 5;    //set x position for next tile
        }
        xPosPtr = tileSize;                 //reset x position
        yPosPtr += (tileSize*2) + 5;        //set y position for next row
    }
}
