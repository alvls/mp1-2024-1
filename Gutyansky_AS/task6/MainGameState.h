#pragma once
#include <string>
#include "GameState.h"
#include "Engine.h"
#include "ScreenBuffer.h"

class MainGameState : public GameState {
private:
    int m_X = 0, m_Y = 0;
public:
    MainGameState(Engine* game) : GameState(game) { }

    int Run() override {
        while (1) {
            Redraw();
            switch (GetEngine()->GetInput())
            {
            case 'w':
                m_Y--;
                break;
            case 's':
                m_Y++;
                break;
            case 'a':
                m_X--;
                break;
            case 'd':
                m_X++;
                break;
            case 'x':
                GetEngine()->SleepMilliseconds(500);
                return -1;
            }
        }
    }

    void Draw(ScreenBuffer& screen) override {
        static std::vector<const char*> sprite = {
            "+-------+",
            "+       +",
            "+       +",
            "+       +",
            "+-------+",
        };

        screen.Write(m_X, m_Y, sprite);
        screen.Write(m_X+8, m_Y, sprite);
        screen.Write(m_X, m_Y+4, sprite);
        screen.Write(m_X+8, m_Y+4, sprite);
    }

};
