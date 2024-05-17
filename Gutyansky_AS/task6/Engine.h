#pragma once
#include <unordered_map>
#include <memory>
#include <conio.h>
#include "GameState.h"
#include "IEngine.h"

class Engine : public IEngine {
private:
    std::unordered_map<int, std::unique_ptr<GameState>> m_GameStates;
    int m_CurrentState;
protected:
    ScreenBuffer m_Screen;

    int GetCurrentState() {
        return m_CurrentState;
    }

    void RegisterState(int id, std::unique_ptr<GameState> gameState) {
        m_GameStates[id] = std::move(gameState);
    }

    virtual int GetStartState() = 0;
    virtual void RegisterStates() = 0;
    virtual void InitializeGame() = 0;
public:
    Engine(size_t width, size_t height) : m_Screen(width, height) { }
    virtual ~Engine() = 0 {};

    ScreenBuffer& GetScreen() {
        return m_Screen;
    }

    int GetInput() {
        return _getch();
    }

    void SleepMilliseconds(int time) {
#ifdef _WIN32
        Sleep(time);
#else
        usleep(time * 1000);
#endif //_WIN32
    }

    void Run() {
        RegisterStates();
        m_CurrentState = GetStartState();

        InitializeGame();
        
        while (m_CurrentState != -1) {
            auto& stateIt = m_GameStates.find(m_CurrentState);
            if (stateIt == m_GameStates.end()) {
                throw "Invalid game state";
            }

            const std::unique_ptr<GameState>& state = stateIt->second;
            m_CurrentState = state->Run();
        }
    }
};