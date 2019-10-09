#pragma once

#include "Engine/Window.h"
#include "Engine/SpriteRenderer2D.h"
#include "Engine/Object2D.h"
#include "Engine/ResourceManager.h"
#include "Level.h"

#include <vector>
#include <iostream>
#include <bitset>

class Game {
public:
    Game(Engine::Window&& window, Engine::SpriteRenderer2D&& renderer) 
    : m_window(window), m_renderer(renderer), m_level(Level{std::bitset<8>{0b10100101}})
    {
        m_level.generate(m_gameObjects, m_window.getWidth(), m_window.getHeight());
    }

    Game(const Game &copy) = delete;

    template <typename... T>
    void addObject(T&&... t) {
        m_gameObjects.emplace_back(std::forward<T>(t)...);
    }

    void update(float deltatime) {
        m_window.processInput(deltatime);
        for(auto &gameObject : m_gameObjects) {
            gameObject.update(m_window.getWidth(), m_window.getHeight());
        }
    }

    void render() {
        for(auto &gameObject : m_gameObjects) {
            m_renderer.draw(gameObject);
        }
    }

    constexpr GLFWwindow& getWindowGLFW() const {
        return m_window.getWindowGLFW();
    }

    constexpr Engine::Window& getWindow() {
        return m_window;
    }

private:
    Engine::Window m_window;
    Engine::SpriteRenderer2D m_renderer;
    std::vector<Engine::Object2D> m_gameObjects;
    Level m_level;
};