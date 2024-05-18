#pragma once
#include <memory>
#include <ctime>
#include "Engine.h"
#include "MainGameState.h"
#include "GameState.h"
#include "BattleshipGameStates.h"

class BattleshipGame final : public Engine {
protected:
    int GetStartState() override {
        return BattleshipGameStates::MainScene;
    }

    void RegisterStates() override {
        RegisterState(BattleshipGameStates::MainScene, std::unique_ptr<GameState>(new MainGameState(this)));
    }

    void InitializeGame() override {
        srand(time(0));

        m_Screen.ShowCursor(false);
    }
public:
    BattleshipGame(size_t width, size_t height) : Engine(width, height) {}
    ~BattleshipGame() override {}
};
