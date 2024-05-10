#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "GameLoop.h"

class Game {
private:
    std::unordered_map<std::string, std::unique_ptr<GameLoop>> m_GameStates;
    std::string m_CurrentState;
protected:
    ScreenBuffer m_Screen;

    const std::string& GetCurrentState() {
        return m_CurrentState;
    }

    void RegisterState(const std::string& name, std::unique_ptr<GameLoop> gameState) {
        m_GameStates[name] = std::move(gameState);
    }

    virtual std::string GetStartState() = 0;
    virtual void RegisterStates() = 0;
    virtual void InitializeGame() = 0;
public:
    Game(size_t width, size_t height) : m_Screen(width, height) { }
    virtual ~Game() = 0 {};

    void ChangeState(const std::string& newState) {
        m_CurrentState = newState;
    }

    void Run() {
        RegisterStates();
        m_CurrentState = GetStartState();

        InitializeGame();
        
        while (m_CurrentState != "EXIT") {
            auto& stateIt = m_GameStates.find(m_CurrentState);
            if (stateIt == m_GameStates.end()) {
                throw "Invalid game state";
            }

            const std::unique_ptr<GameLoop>& state = stateIt->second;
            state->OnUpdate();

            m_Screen.Clear();
            state->OnDraw(m_Screen);
            m_Screen.Flush();
        }
    }
};