#include "SplashScene.hpp"
#include "../../GameManager.hpp"
#include "../ResourceManager.hpp"
#include "MainMenuScene.hpp"
#include "../FontRenderer.hpp"

SplashScene::SplashScene()
{
    splashLogo = ResourceManager::loadTexture("res/splash.png");
}

SplashScene::~SplashScene()
{
    SDL_DestroyTexture(splashLogo);
    splashLogo = nullptr;
}

void SplashScene::update()
{
    if (fading)
    {
        if (fadeIn)
        {
            curAlpha++;

            if (curAlpha == 255)
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
            menuScene = new MainMenuScene();
        }
    }
}

void SplashScene::render(SDL_Renderer* renderer)
{
    SDL_Rect drawRect;
    drawRect.x = 0;
    drawRect.y = 0;
    drawRect.w = 800;
    drawRect.h = 600;

    SDL_SetTextureAlphaMod(splashLogo, curAlpha);
    SDL_RenderCopy(renderer, splashLogo, nullptr, nullptr);
}

void SplashScene::handelEvent(SDL_Event e)
{

}
