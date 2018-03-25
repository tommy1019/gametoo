#ifndef MainMenuScene_hpp
#define MainMenuScene_hpp

#include "Scene.hpp"
#include "../RenderObject.hpp"

class MainMenuScene : public Scene
{
private:
    RenderObject* spButtonLeft;
    RenderObject* spButtonMiddle;
    RenderObject* spButtonRight;

    RenderObject* spButtonLeftPress;
    RenderObject* spButtonMiddlePress;
    RenderObject* spButtonRightPress;

    RenderObject* mpButtonLeft;
    RenderObject* mpButtonMiddle;
    RenderObject* mpButtonRight;

    RenderObject* mpButtonLeftPress;
    RenderObject* mpButtonMiddlePress;
    RenderObject* mpButtonRightPress;

    bool spPressed = false;
    bool mpPressed = false;
public:
    MainMenuScene();
    ~MainMenuScene();

    void render() override;
    void handelEvent(SDL_Event e) override;
};

#endif
