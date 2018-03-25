#include "GameScene.hpp"

#include <iostream>

#include "../Render.hpp"
#include "../ResourceManager.hpp"
#include "../FontRenderer.hpp"

#include "../../World.hpp"

#include "../../net/ConnectionManager.hpp"
#include "../../event/CreateUnitEvent.hpp"

GameScene::GameScene(GameState* clientGameState)
{
    this->clientGameState = clientGameState;

    clientGameState->world = new World();

    Chunk* chunk = new Chunk(0, 0);
    clientGameState->world->chunkList.push_back(chunk);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            view[i][j] = 0;

    view[0][0] = 0.1;
    view[1][1] = 0.1;
    view[2][2] = 1;
    view[3][3] = 1;
}

void GameScene::update()
{
    if (ConnectionManager::unprocessedPackets.size() > 0)
    {
        SDL_SemWait(ConnectionManager::dataLock);

        for (Packet* p : ConnectionManager::unprocessedPackets)
        {
            switch (p->packetId)
            {
                case 1:
                {
                    CreateUnitEvent* createUnitEvent = (CreateUnitEvent*)p->data;

                    Unit* unit = new Unit(createUnitEvent->x, createUnitEvent->y);
                    unit->renderObject = new RenderObject("res/gameSheet.png", 0, 0);
                    unit->renderObject->setPos(createUnitEvent->x, createUnitEvent->y, 1, 1);

                    clientGameState->units.push_back(unit);

                    delete createUnitEvent;
                }
                    break;
            }
        }

        ConnectionManager::unprocessedPackets.clear();

        SDL_SemPost(ConnectionManager::dataLock);
    }
}

void GameScene::render()
{
    view[0][0] = scale;
    view[1][1] = scale;

    view[3][0] = -x * scale;
    view[3][1] = -y * scale;

    Render::updateProjection(view[0]);

	clientGameState->world->render();

    FontRenderer::renderString("Click to place units", 0, 0, 20);

    for (Unit* u : clientGameState->units)
    {
        u->renderObject->render();
    }
}

void GameScene::handelEvent(SDL_Event e)
{
    if (e.type == SDL_MOUSEBUTTONUP && e.button.button == 3)
    {
        int mxI, myI;
        SDL_GetMouseState(&mxI, &myI);
        double mx = mxI / 400.0 - 1;
        double my = (-myI / 300.0 + 1);

        std::cout << mx << ", " << my << std::endl;

        CreateUnitEvent e;
        e.x = x + (mx / scale);
        e.y = y + (my / scale * 6.0 / 8.0);

        ConnectionManager::sendToServer(1, sizeof(CreateUnitEvent), &e);
    }
    else if (e.type == SDL_MOUSEMOTION)
    {
        if (e.button.button == 1)
        {
            x -= e.motion.xrel * (scale / 2);
            y += e.motion.yrel * (scale / 2);
        }
    }
    else if(e.type == SDL_MOUSEWHEEL)
    {
        scale += e.wheel.y / 300.0;
        if (scale <= 0.001)
            scale = 0.001;
    }
}
