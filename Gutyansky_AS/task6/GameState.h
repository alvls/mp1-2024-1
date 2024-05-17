#pragma once
#include "ScreenBuffer.h"
#include "IEngine.h"

class GameState {
private:
    IEngine* m_Game;
protected:
    virtual void Draw(ScreenBuffer& screen) = 0;

    void Redraw() {
        ScreenBuffer& screen = m_Game->GetScreen();
        screen.Clear();
        Draw(screen);
        screen.Flush();
    }
public:
    GameState(IEngine* game) : m_Game(game) { }
    virtual ~GameState() = 0 {}

    virtual int Run() = 0;

    IEngine* GetEngine() {
        return m_Game;
    }
};