#ifndef CreateMPGameScene_hpp
#define CreateMPGameScene_hpp

#include "Scene.hpp"

class CreateMPGameScene : public Scene
{
private:
    bool rendered = false;
public:
    void update() override;
    void render(SDL_Renderer* renderer) override;
};

#endif
