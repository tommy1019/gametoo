#ifndef GameScene_hpp
#define GameScene_hpp

#include "Scene.hpp"

#include "../../GameState.hpp"

class GameScene : public Scene
{
public:
    GameState* clientGameState;

    float scale = 0.1;
    float x = 0;
    float y = 0;

    float view[4][4];

    GameScene(GameState* clientGameState);

    void update() override;
    void render() override;
    void handelEvent(SDL_Event e) override;
};

#endif
