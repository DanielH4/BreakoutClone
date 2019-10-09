#include "Engine/Window.h"
#include "Engine/Object2D.h"
#include "Engine/SpriteRenderer2D.h"
#include "Engine/ResourceManager.h"
#include "Game.h"

#include <iostream>

int main() {

    Engine::Window window{800, 600, "GameEngine"};
    Engine::SpriteRenderer2D renderer{Engine::createShader("../src/shaders/shader.vs", "../src/shaders/shader.fs")};
    Game game{  std::move(window),
                std::move(renderer)};

    /*
    Engine::Object2D container(Engine::Texture{"../src/res/textures/container.jpg"},
                    glm::vec2(400, 400),
                    glm::vec2(50, 50),
                    45.0f);

    Engine::Object2D steelContainer(Engine::Texture{"../src/res/textures/steel_container.png"},
                    glm::vec2(400, 200),
                    glm::vec2(50, 50),
                    45.0f);

    game.addObject(container);
    game.addObject(steelContainer);
    */

    game.addObject(Engine::loadTexture("../src/res/textures/container.jpg"),
                    glm::vec2{400, 400},
                    glm::vec2{50, 50},
                    0.0f);

    game.addObject(Engine::loadTexture("../src/res/textures/awesomeface.png"),
                    glm::vec2{200, 200},
                    glm::vec2{50, 50},
                    0.0f);
    
    while(!glfwWindowShouldClose(&game.getWindowGLFW())) {
        static float s_deltatime = 0.0f;
        static float s_lastFrame = 0.0f;
        float currentFrame = glfwGetTime();
        s_deltatime = currentFrame - s_lastFrame;
        s_lastFrame = currentFrame;

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        game.render();
        game.update(s_deltatime);
        
        glfwSwapBuffers(&game.getWindowGLFW());
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}