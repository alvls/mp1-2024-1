#pragma once

#include "Player.h"
#include <random>

class ComputerPlayer : public Player 
{
public:
    ComputerPlayer(Board& board);
    void placeShips() override;
    bool takeTurn(Player& opponent) override;

private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
};

