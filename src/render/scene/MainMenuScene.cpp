#include "MainMenuScene.hpp"

#include <iostream>

#include "../../GameManager.hpp"
#include "../ResourceManager.hpp"
#include "../FontRenderer.hpp"
#include "CreateSPGameScene.hpp"
#include "CreateMPGameScene.hpp"

MainMenuScene::MainMenuScene()
{
    spButtonLeft = new RenderObject("res/menuSheet.png", 0, 0);
    spButtonLeft->setPos(400 - 64 - 32, 300 - 32, 64, 64);

    spButtonMiddle = new RenderObject("res/menuSheet.png", 1, 0);
    spButtonMiddle->setPos(400 - 32, 300 - 32, 64, 64);

    spButtonRight = new RenderObject("res/menuSheet.png", 2, 0);
    spButtonRight->setPos(400 + 32, 300 - 32, 64, 64);

    mpButtonLeft = new RenderObject("res/menuSheet.png", 0, 0);
    mpButtonLeft->setPos(400 - 64 - 32, 400 - 32, 64, 64);

    mpButtonMiddle = new RenderObject("res/menuSheet.png", 1, 0);
    mpButtonMiddle->setPos(400 - 32, 400 - 32, 64, 64);

    mpButtonRight = new RenderObject("res/menuSheet.png", 2, 0);
    mpButtonRight->setPos(400 + 32, 400 - 32, 64, 64);
}

MainMenuScene::~MainMenuScene()
{
    delete spButtonLeft;
    delete spButtonMiddle;
    delete spButtonRight;

    delete mpButtonLeft;
    delete mpButtonMiddle;
    delete mpButtonRight;
}

void MainMenuScene::render()
{
    spButtonLeft->render();
    spButtonMiddle->render();
    spButtonRight->render();

    mpButtonLeft->render();
    mpButtonMiddle->render();
    mpButtonRight->render();

    FontRenderer::renderString("GameToo", 400 - FontRenderer::pixelLength("GameToo", 50) / 2, 100, 50);

    FontRenderer::renderString("Single Player", 400 - FontRenderer::pixelLength("Single Player", 10) / 2, 300 - 10, 10);
    FontRenderer::renderString("Multiplayer", 400 - FontRenderer::pixelLength("Multiplayer", 10) / 2, 400 - 10, 10);
}

void MainMenuScene::handelEvent(SDL_Event e)
{
    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONUP)
    {
        int mx, my;
        SDL_GetMouseState(&mx, &my);

        if (mx > 400 - 64 - 32 && my > 300 - 32 && mx < 400 + 32 + 64 && my < 300 + 32)
        {
            spButtonLeft->setClip(0, 1);
            spButtonMiddle->setClip(1, 1);
            spButtonRight->setClip(2, 1);

            if (e.type == SDL_MOUSEBUTTONUP)
            {
                GameManager::nextScene = new CreateSPGameScene;
            }
        }
        else
        {
            spButtonLeft->setClip(0, 0);
            spButtonMiddle->setClip(1, 0);
            spButtonRight->setClip(2, 0);
        }

        if (mx > 400 - 64 - 32 && my > 400 - 32 && mx < 400 + 32 + 64 && my < 400 + 32)
        {
            mpButtonLeft->setClip(0, 1);
            mpButtonMiddle->setClip(1, 1);
            mpButtonRight->setClip(2, 1);

            if (e.type == SDL_MOUSEBUTTONUP)
            {
                GameManager::nextScene = new CreateMPGameScene;
            }
        }
        else
        {
            mpButtonLeft->setClip(0, 0);
            mpButtonMiddle->setClip(1, 0);
            mpButtonRight->setClip(2, 0);
        }
    }
}
