#ifndef CreateSPGameScene_hpp
#define CreateSPGameScene_hpp

#include "Scene.hpp"

class CreateSPGameScene : public Scene
{
private:
    bool rendered = false;
public:
    void update() override;
    void render() override;
};

#endif
