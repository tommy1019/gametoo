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
    spButtonLeft->setPos(-0.3, -0.1, 0.2, 0.2);
    spButtonMiddle = new RenderObject("res/menuSheet.png", 1, 0);
    spButtonMiddle->setPos(-0.1, -0.1, 0.2, 0.2);
    spButtonRight = new RenderObject("res/menuSheet.png", 2, 0);
    spButtonRight->setPos(0.1, -0.1, 0.2, 0.2);

    spButtonLeftPress = new RenderObject("res/menuSheet.png", 0, 1);
    spButtonLeftPress->setPos(-0.3, -0.1, 0.2, 0.2);
    spButtonMiddlePress = new RenderObject("res/menuSheet.png", 1, 1);
    spButtonMiddlePress->setPos(-0.1, -0.1, 0.2, 0.2);
    spButtonRightPress = new RenderObject("res/menuSheet.png", 2, 1);
    spButtonRightPress->setPos(0.1, -0.1, 0.2, 0.2);

    mpButtonLeft = new RenderObject("res/menuSheet.png", 0, 0);
    mpButtonLeft->setPos(-0.3, -0.4, 0.2, 0.2);
    mpButtonMiddle = new RenderObject("res/menuSheet.png", 1, 0);
    mpButtonMiddle->setPos(-0.1, -0.4, 0.2, 0.2);
    mpButtonRight = new RenderObject("res/menuSheet.png", 2, 0);
    mpButtonRight->setPos(0.1, -0.4, 0.2, 0.2);

    mpButtonLeftPress = new RenderObject("res/menuSheet.png", 0, 1);
    mpButtonLeftPress->setPos(-0.3, -0.4, 0.2, 0.2);
    mpButtonMiddlePress = new RenderObject("res/menuSheet.png", 1, 1);
    mpButtonMiddlePress->setPos(-0.1, -0.4, 0.2, 0.2);
    mpButtonRightPress = new RenderObject("res/menuSheet.png", 2, 1);
    mpButtonRightPress->setPos(0.1, -0.4, 0.2, 0.2);
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
    if (spPressed)
    {
        spButtonLeftPress->render();
        spButtonMiddlePress->render();
        spButtonRightPress->render();
    }
    else
    {
        spButtonLeft->render();
        spButtonMiddle->render();
        spButtonRight->render();
    }

    if (mpPressed)
    {
        mpButtonLeftPress->render();
        mpButtonMiddlePress->render();
        mpButtonRightPress->render();
    }
    else
    {
        mpButtonLeft->render();
        mpButtonMiddle->render();
        mpButtonRight->render();
    }

    FontRenderer::renderString("GameToo", 400 - FontRenderer::pixelLength("GameToo", 50) / 2, 100, 50);

    FontRenderer::renderString("Single Player", 400 - FontRenderer::pixelLength("Single Player", 10) / 2, 300 - 10, 10);
    FontRenderer::renderString("Multiplayer", 400 - FontRenderer::pixelLength("Multiplayer", 10) / 2, 400 - 10, 10);
}

void MainMenuScene::handelEvent(SDL_Event e)
{
    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONUP)
    {
        int mxI, myI;
        SDL_GetMouseState(&mxI, &myI);
        double mx = mxI / 400.0 - 1;
        double my = (-myI / 300.0 + 1) * (600.0 / 800.0);

        if (e.type == SDL_MOUSEBUTTONUP)
        {
            std::cout << mx << ", " << my << std::endl;
        }

        if (mx > -0.3 && my < 0.1 && mx < 0.3 && my > -0.1)
        {
            spPressed = true;
            if (e.type == SDL_MOUSEBUTTONUP)
            {
                GameManager::nextScene = new CreateSPGameScene;
            }
        }
        else
        {
            spPressed = false;
        }

        if (mx > -0.3 && my > -0.4 && mx < 0.3 && my < -0.2)
        {
            mpPressed = true;

            if (e.type == SDL_MOUSEBUTTONUP)
            {
                GameManager::nextScene = new CreateMPGameScene;
            }
        }
        else
        {
            mpPressed = false;
        }
    }
}
