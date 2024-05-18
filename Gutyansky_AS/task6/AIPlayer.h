#pragma once
#include <vector>
#include <utility>
#include "Player.h"
#include "Ship.h"

class AIPlayer final : public Player {
public:
    AIPlayer(int boardSize, const std::vector<Ship>& ships) : Player(boardSize, ships) { }

    std::pair<int, int> GetMove() override {
        return { 0, 0 };
    }
};
