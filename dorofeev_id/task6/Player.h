#pragma once

#include "Board.h"

class Player 
{
public:
    Player(Board& board);
    virtual void placeShips() = 0;
    virtual bool takeTurn(Player& opponent) = 0;
    Board& getBoard();

protected:
    Board& board;
};
