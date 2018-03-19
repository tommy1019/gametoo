#include "CreateSPGameScene.hpp"

#include "../FontRenderer.hpp"

#include "CreateMPGameScene.hpp"

#include "../../GameManager.hpp"
#include "../../net/ConnectionManager.hpp"

void CreateSPGameScene::update()
{
    if (rendered)
    {
        //Start server
        ConnectionManager::startMPServer();

        GameManager::nextScene = new CreateMPGameScene;
    }
    rendered = true;
}

void CreateSPGameScene::render(SDL_Renderer *renderer)
{
    FontRenderer::renderString(renderer, "Creating server", 400 - FontRenderer::pixelLength("Creating server", 25) / 2, 300 - 32, 25);
}
