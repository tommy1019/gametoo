#include "CreateMPGameScene.hpp"

#include "../FontRenderer.hpp"

#include "GameScene.hpp"

#include "../../GameManager.hpp"
#include "../../net/ConnectionManager.hpp"

void CreateMPGameScene::update()
{
    if (rendered)
    {
        GameState* gameState = new GameState;

        //Connect to server
        ConnectionManager::connectToServer(gameState);

        GameManager::nextScene = new GameScene(gameState);
    }
    rendered = true;
}

void CreateMPGameScene::render(SDL_Renderer *renderer)
{
    FontRenderer::renderString(renderer, "Connecting to server", 400 - FontRenderer::pixelLength("Connecting to server", 25) / 2, 300 - 32, 25);
}
