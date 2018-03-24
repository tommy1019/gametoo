#include "CreateMPGameScene.hpp"

#include "../FontRenderer.hpp"

#include "GameScene.hpp"

#include "../../GameManager.hpp"
#include "../../net/ConnectionManager.hpp"

void CreateMPGameScene::update()
{
    if (connecting)
    {
        return;
    }

    if (rendered)
    {
        //Connect to server
        ConnectionManager::connectToServer();
        connecting = true;
    }
    rendered = true;
}

void CreateMPGameScene::render()
{
    FontRenderer::renderString("Connecting to server", 400 - FontRenderer::pixelLength("Connecting to server", 25) / 2, 300 - 32, 25);
}
