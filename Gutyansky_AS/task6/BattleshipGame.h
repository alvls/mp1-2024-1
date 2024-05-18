#pragma once
#include <memory>
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
        m_Screen.ShowCursor(false);
    }
public:
    BattleshipGame(size_t width, size_t height) : Engine(width, height) {}
    ~BattleshipGame() override {}
};
