#include <iostream>

#include "SplashScene.hpp"
#include "../../GameManager.hpp"
#include "../ResourceManager.hpp"
#include "MainMenuScene.hpp"
#include "../FontRenderer.hpp"
#include "../../Chunk.hpp"
#include "../Render.hpp"

SplashScene::SplashScene()
{
    splashLogo = ResourceManager::loadTexture("res/splash.png");
}

SplashScene::~SplashScene()
{
    std::cout << "Still not cleaning up textures splash screen" << std::endl;
}

void SplashScene::update()
{
    if (fading)
    {
        if (fadeIn)
        {
            curAlpha++;

            if (curAlpha == 10)
            {
                fading = false;
                fadeIn = false;
            }
        }
        else
        {
            curAlpha--;

            if (curAlpha == 0)
            {
                GameManager::nextScene = menuScene;
            }
        }
    }
    else
    {
        delay--;


        if (delay == 0)
        {
            fading = true;

            //Loading
            FontRenderer::loadFont();
            ResourceManager::preLoadTexture("res/gameSheet.png");
            Chunk::loadTextures();
            menuScene = new MainMenuScene();
        }
    }
}

void SplashScene::render()
{
    Render::renderQuad(mvp[0], splashLogo);
}

void SplashScene::handelEvent(SDL_Event e)
{

}
