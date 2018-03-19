#include "FontRenderer.hpp"

#include <iostream>

#include "ResourceManager.hpp"

SDL_Texture* FontRenderer::fontTexture;

SDL_Rect FontRenderer::upperClips[26];
SDL_Rect FontRenderer::lowerClips[26];

void FontRenderer::loadFont()
{
    fontTexture = ResourceManager::loadTexture("res/font.png");

    for (int i = 0; i < 26; i++)
    {
        SDL_Rect uRect;
        uRect.x = i * 5;
        uRect.y = 0;
        uRect.w = 5;
        uRect.h = 7;
        upperClips[i] = uRect;

        SDL_Rect lRect;
        lRect.x = i * 5;
        lRect.y = 7;
        lRect.w = 5;
        lRect.h = 11;
        lowerClips[i] = lRect;
    }
}

void FontRenderer::renderString(SDL_Renderer* renderer, std::string txt, int x, int y, float size)
{
    int charWidth = ceil(size);
    int uCharHeight = ceil(size * (7.0 / 5.0));
    int lCharHeight = ceil(size * (11.0 / 5.0));
    int spaceWidth = ceil(size * 0.2);

    x -= charWidth + spaceWidth;

    for (char c : txt)
    {
        int index = static_cast<int>(c);

        x += charWidth + spaceWidth;

        if (index == 32)
            continue;

        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = charWidth;

        if (index < 96)
        {
            rect.h = uCharHeight;
            SDL_RenderCopy(renderer, fontTexture, &upperClips[index - 65], &rect);
        }
        else
        {
            rect.h = lCharHeight;
            SDL_RenderCopy(renderer, fontTexture, &lowerClips[index - 97], &rect);
        }

    }
}

int FontRenderer::pixelLength(std::string str, float size)
{
    return ceil(size) * str.length() + ceil(size * 0.2) * (str.length() - 1);
}
