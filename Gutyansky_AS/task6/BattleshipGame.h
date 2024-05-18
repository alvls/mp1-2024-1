#pragma once
#include <memory>
#include <ctime>
#include "Engine.h"
#include "BattleState.h"
#include "PlacementState.h"
#include "GameState.h"
#include "BattleshipGameStates.h"

class BattleshipGame final : public Engine {
private:
    BattleshipGameData m_GameData;

protected:
    int GetStartState() override {
        return BattleshipGameStates::Placement;
    }

    void RegisterStates() override {
        RegisterState(BattleshipGameStates::Placement, std::unique_ptr<GameState>(new PlacementState(&m_GameData, this)));
        RegisterState(BattleshipGameStates::Battle, std::unique_ptr<GameState>(new BattleState(&m_GameData, this)));
    }

    void InitializeGame() override {
        srand(time(0));

        m_Screen.ShowCursor(false);
    }
public:
    BattleshipGame(size_t width, size_t height) : Engine(width, height), m_GameData(10) {}
    ~BattleshipGame() override {}
};
