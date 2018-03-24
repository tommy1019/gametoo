#ifndef FontRenderer_hpp
#define FontRenderer_hpp

#include <GL/glew.h>

#include <string>

class FontRenderer
{
private:
    static GLuint fontTexture;

public:
    static void loadFont();

    static void renderString(std::string txt, int x, int y, float size);
    static int pixelLength(std::string str, float size);
};

#endif
