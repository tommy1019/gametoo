#ifndef CreateMPGameScene_hpp
#define CreateMPGameScene_hpp

#include "Scene.hpp"

class CreateMPGameScene : public Scene
{
private:
    bool rendered = false;
    bool connecting = false;
public:
    void update() override;
    void render() override;
};

#endif
