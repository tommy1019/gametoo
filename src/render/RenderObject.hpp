#ifndef RenderObject_hpp
#define RenderObject_hpp

#include <string>

#include <GL/glew.h>

class RenderObject
{
private:
    GLuint texture;

    GLuint tbo;

    GLfloat mvp[4][4];

public:
    RenderObject(std::string path, int sx, int sy, int sw = 32, int sh = 32, int textSheetSize = 512);
    ~RenderObject();

    void render();

    void setPos(double x, double y, double w, double h);
};

#endif
