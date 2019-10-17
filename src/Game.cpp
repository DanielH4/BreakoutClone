#include "Game/Game.h"

Game::Game(const Engine::Window& window, const Engine::SpriteRenderer2D& renderer) 
:   m_window(window), 
    m_renderer(renderer), 
    m_ball(Engine::Object2D{Engine::loadTexture("../res/textures/steel_container.png"), glm::vec2{400, 300}, glm::vec2{20, 20}, 0.0f}), 
    m_level(1),
    m_player(Engine::Texture{"../res/textures/container.jpg"}, glm::vec2{400, 580}, glm::vec2{80, 5}, &getWindowGLFW()),
    m_shouldUpdate(true)
{
    m_level.generate(m_gameObjects);
    m_ball.setVelocity(3.0f, -3.0f);
}

/*
//optimized: takes Object2D constructor parameter and constructs an object added to gameobject vector.
template <typename... T>
void Game::addObject(T&&... t) {
    m_gameObjects.emplace_back(std::forward<T>(t)...);
}
*/

/*
void Game::addObject(std::unique_ptr<Engine::Object2D> object) {
    m_gameObjects.push_back(object);
}
*/

void Game::update(float deltatime) {

    m_window.processInput(deltatime);
    if(m_shouldUpdate) {
        if(m_ball.isOutOfBounds()) {
            m_shouldUpdate = false;
            //glfwSetWindowShouldClose(&getWindowGLFW(), true);
        }

        int screenWidth = m_window.getWidth();
        int screenHeight = m_window.getHeight();

        //handle player/ball updates and collisions
        m_player.processInput(deltatime);
        m_player.update(screenWidth, screenHeight);
        m_ball.update(screenWidth, screenHeight);
        if(m_player.collidesWith(m_ball)) {
            m_player.handleCollision(m_ball);
        }

        for(auto objIter = m_gameObjects.begin(); objIter != m_gameObjects.end(); ++objIter) {
            (*objIter)->update(screenWidth, screenHeight);
            //ball collisions with tiles
            if(m_ball.collidesWith(**objIter) && (*objIter)->type() == "Tile") {
                m_ball.handleCollision(**objIter);
                //spawn powerup
                m_gameObjects.push_back(new Powerup(Powerup::Effect::ENLARGE, 
                                                    Engine::Texture("../res/awesomeface.png", GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE),
                                                    (*objIter)->getPosition(),
                                                    (*objIter)->getSize() / 1.7f,
                                                    glm::vec2{0, 1}));
                //delete(*objIter);
                m_gameObjects.erase(objIter);   //leaking memory
            }

            //player collisions with powerups
            if(m_player.collidesWith(**objIter) && (*objIter)->type() == "Powerup") {
                Powerup::Effect effect = dynamic_cast<Powerup&>(**objIter).getEffect();
                m_player.addPowerup(effect);
                //delete(*objIter);
                m_gameObjects.erase(objIter);   //leaking memory
            }
        }
    }
}

void Game::render() {
    for(auto &gameObject : m_gameObjects) {
        m_renderer.draw(*gameObject);
    }
    m_renderer.draw(m_player);
    m_renderer.draw(m_ball);
}

GLFWwindow& Game::getWindowGLFW() {
    return m_window.getWindowGLFW();
}

Engine::Window& Game::getWindow() {
    return m_window;
}