#pragma once
#include "Game.h"
#include "MainGameState.h"
#include "GameLoop.h"

class BattleshipGame : public Game {
protected:
    std::string GetStartState() override {
        return "MAIN";
    }

    void RegisterStates() override {
        RegisterState("MAIN", std::unique_ptr<GameLoop>(new MainGameState(this)));
    }

    void InitializeGame() override {
        m_Screen.ShowCursor(false);
    }
public:
    BattleshipGame(size_t width, size_t height) : Game(width, height) {}
    ~BattleshipGame() override {}
};
