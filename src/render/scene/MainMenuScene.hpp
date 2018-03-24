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

    RenderObject* mpButtonLeft;
    RenderObject* mpButtonMiddle;
    RenderObject* mpButtonRight;
public:
    MainMenuScene();
    ~MainMenuScene();

    void render() override;
    void handelEvent(SDL_Event e) override;
};

#endif
