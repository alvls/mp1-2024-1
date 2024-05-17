#pragma once
#include <conio.h>
#include "GameLoop.h"
#include "Game.h"
#include "ScreenBuffer.h"

class MainGameState : public GameLoop {
private:
    int m_X = 0, m_Y = 0;
public:
    MainGameState(Game* game) : GameLoop(game) { }

    void OnUpdate() override {
        if (_kbhit()) {
            switch (_getch())
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
                GetEngine()->ChangeState("EXIT");
                break;
            }

        }
    }

    void OnDraw(ScreenBuffer& screen) override {
        static char line[] = "+-------+";
        static char empty[] = "+       +";

        screen.Clear();

        screen.Write(m_X, m_Y, line, sizeof(line) - 1);
        screen.Write(m_X, m_Y + 1, empty, sizeof(empty) - 1);
        screen.Printf(m_X, m_Y + 2, "+ %02d-%02d +", m_X, m_Y);
        screen.Write(m_X, m_Y + 3, empty, sizeof(empty) - 1);
        screen.Write(m_X, m_Y + 4, line, sizeof(line) - 1);

        screen.Flush();

#ifdef _WIN32
        Sleep(30);
#else
        usleep(30000);
#endif //_WIN32
    }

};
