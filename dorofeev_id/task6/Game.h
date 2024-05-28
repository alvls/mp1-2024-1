#pragma once

#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

class Game 
{
public:
    Game();
    void play();

private:
    Board humanBoard;
    Board computerBoard;
    HumanPlayer humanPlayer;
    ComputerPlayer computerPlayer;
};

