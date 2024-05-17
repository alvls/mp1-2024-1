#pragma once
#include "ScreenBuffer.h"

class Game;

class GameLoop {
private:
    Game* m_Game;
public:
    GameLoop(Game* game) : m_Game(game) { }
    virtual ~GameLoop() = 0 {}

    Game* GetEngine() {
        return m_Game;
    }

    virtual void OnUpdate() = 0;
    virtual void OnDraw(ScreenBuffer& screen) = 0;
};