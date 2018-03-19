#ifndef FontRenderer_hpp
#define FontRenderer_hpp

#include <SDL.h>

#include <string>

class FontRenderer
{
private:
    static SDL_Texture* fontTexture;

    static SDL_Rect upperClips[26];
    static SDL_Rect lowerClips[26];

public:
    static void loadFont();

    static void renderString(SDL_Renderer* renderer, std::string txt, int x, int y, float size);
    static int pixelLength(std::string str, float size);
};

#endif
