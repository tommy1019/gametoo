#include "GameScene.hpp"

#include <iostream>

#include "../ResourceManager.hpp"
#include "../FontRenderer.hpp"

#include "../../World.hpp"

#include "../../net/ConnectionManager.hpp"
#include "../../event/CreateUnitEvent.hpp"

GameScene::GameScene(GameState* clientGameState)
{
    this->clientGameState = clientGameState;

    clientGameState->world = new World();

    Chunk* chunk = new Chunk();
    clientGameState->world->chunkList.push_back(chunk);
}

void GameScene::render()
{
	clientGameState->world->render();

    FontRenderer::renderString("Click to place units", 0, 0, 20);

    for (Unit* u : clientGameState->units)
    {
        u->draw();
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
}
