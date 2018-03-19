#include "GameScene.hpp"

#include <iostream>

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
        Unit* u = new Unit(mx - 32, my - 32);
        clientGameState->units.push_back(u);
        std::cout << "Adding unit " << mx << " " << my << std::endl;
    }
}
