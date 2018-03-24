#ifndef RenderObject_hpp
#define RenderObject_hpp

#include <string>

#include <GL/glew.h>

class RenderObject
{
private:
    GLuint texture;
public:
    RenderObject(std::string path, int sx, int sy);
    ~RenderObject();

    void render();

    void setClip(int x, int y);
    void setPos(int x, int y, int w, int h);
};

#endif
