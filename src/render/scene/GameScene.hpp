#ifndef GameScene_hpp
#define GameScene_hpp

#include "Scene.hpp"

#include "../../GameState.hpp"

class GameScene : public Scene
{
public:
    GameState* clientGameState;

    GameScene(GameState* clientGameState);

    void render(SDL_Renderer* renderer) override;
    void handelEvent(SDL_Event e) override;
};

#endif
