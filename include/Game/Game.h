#pragma once

#include "Engine/Window.h"
#include "Engine/SpriteRenderer2D.h"
#include "Engine/Object2D.h"
#include "Engine/ResourceManager.h"
#include "Game/Player.h"
#include "Game/Level.h"
#include "Game/Tile.h"
#include "Game/Powerup.h"

#include <vector>
#include <iostream>
#include <bitset>
#include <utility>
#include <memory>

class Game {
public:
    Game(const Engine::Window& window, const Engine::SpriteRenderer2D& renderer);
    Game(const Game &copy) = delete;

    /*
    //optimized: takes Object2D constructor parameter and constructs an object added to gameobject vector.
    template <typename... T>
    void addObject(T&&... t);
    */

    //void addObject(Engine::Object2D* object);
    void update(float deltatime);
    void render();
    GLFWwindow& getWindowGLFW();
    Engine::Window& getWindow();

private:
    Engine::Window m_window;
    Engine::SpriteRenderer2D m_renderer;
    std::vector<Engine::Object2D*> m_gameObjects;
    Level m_level;
    Engine::Object2D m_ball;
    Player m_player;
    bool m_shouldUpdate;
};