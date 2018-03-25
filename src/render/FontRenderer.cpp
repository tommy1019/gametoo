#include "FontRenderer.hpp"

#include <iostream>

#include "ResourceManager.hpp"

GLuint FontRenderer::fontTexture;

void FontRenderer::loadFont()
{
    fontTexture = ResourceManager::loadTexture("res/font.png");
}

void FontRenderer::renderString(std::string txt, int x, int y, float size)
{
    int charWidth = ceil(size);
    //int uCharHeight = ceil(size * (7.0 / 5.0));
    //int lCharHeight = ceil(size * (11.0 / 5.0));
    int spaceWidth = ceil(size * 0.2);

    x -= charWidth + spaceWidth;

    for (char c : txt)
    {
        int index = static_cast<int>(c);

        x += charWidth + spaceWidth;

        if (index == 32)
            continue;

        if (index < 96)
        {
            //SDL_RenderCopy(renderer, fontTexture, &upperClips[index - 65], &rect);
        }
        else
        {
            //SDL_RenderCopy(renderer, fontTexture, &lowerClips[index - 97], &rect);
        }

    }
}

int FontRenderer::pixelLength(std::string str, float size)
{
    return ceil(size) * str.length() + ceil(size * 0.2) * (str.length() - 1);
}
