#ifndef Unit_hpp
#define Unit_hpp

#include "render/RenderObject.hpp"

class Unit
{
public:
    RenderObject* renderObject;

    double x, y;

    Unit(double x, double y);

    void draw();
};

#endif
