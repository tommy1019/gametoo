#ifndef SplashScene_hpp
#define SplashScene_hpp

#include <GL/glew.h>

#include "Scene.hpp"
#include "MainMenuScene.hpp"

class SplashScene : public Scene
{
private:
    MainMenuScene* menuScene;
    GLuint splashLogo;

    bool fading = true;
    bool fadeIn = true;
    int curAlpha = 0;
    int delay = 300;

public:
    SplashScene();
    ~SplashScene();

    virtual void update() override;
    virtual void render() override;
    virtual void handelEvent(SDL_Event e) override;
};

#endif
