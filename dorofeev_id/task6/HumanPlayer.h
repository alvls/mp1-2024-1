#pragma once

#include "Player.h"

class HumanPlayer : public Player 
{
public:
    HumanPlayer(Board& board);
    void placeShips() override;
    bool takeTurn(Player& opponent) override;
};

