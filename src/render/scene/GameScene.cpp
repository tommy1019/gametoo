#include "GameScene.hpp"

#include <iostream>

#include "../../net/ConnectionManager.hpp"
#include "../../CreateUnitEvent.hpp"
#include "../../UpdateStateEvent.hpp"

#include "../ResourceManager.hpp"
#include "../FontRenderer.hpp"

GameScene::GameScene(GameState* clientGameState)
{
    this->clientGameState = clientGameState;
}

void GameScene::render(SDL_Renderer *renderer)
{
    FontRenderer::renderString(renderer, "Click to place units", 0, 0, 20);

    for (Unit* u : clientGameState->units)
    {
        u->draw(renderer);
    }
}

void GameScene::handelEvent(SDL_Event e)
{
    if (e.type == SDL_MOUSEBUTTONUP)
    {
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        CreateUnitEvent e;
        e.x = mx - 32;
        e.y = my - 32;

        ConnectionManager::sendToServer(1, &e);
        std::cout << "[Client] Sent create unit packet " << mx << " " << my << std::endl;
    }

    if (e.type == SDL_KEYDOWN)
    {
        UpdateStateEvent e;
        e.stepNum = 0;
        ConnectionManager::sendToServer(2, &e);
        std::cout << "[Client] Sent update event" << std::endl;
    }
}
