#include "Unit.hpp"

Unit::Unit(int x, int y): render("res/gameSheet.png", 0, 0)
{
    render.setPos(x, y, 64, 64);
}

void Unit::draw(SDL_Renderer* renderer)
{
    render.render(renderer);
}
