#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(Board& board)
    : Player(board), gen(rd()), dis(0, 9) {}

void ComputerPlayer::placeShips() 
{
    int shipSizes[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
    for (int size : shipSizes) 
    {
        bool placed = false;
        while (!placed) 
        {
            int x1 = dis(gen), y1 = dis(gen);
            int direction = dis(gen) % 2; // 0 - horizontal, 1 - vertical
            int x2 = direction == 0 ? x1 : x1 + size - 1;
            int y2 = direction == 0 ? y1 + size - 1 : y1;
            if (x2 < 10 && y2 < 10 && board.placeShip(x1, y1, x2, y2, size)) 
            {
                placed = true;
            }
        }
    }
}

bool ComputerPlayer::takeTurn(Player& opponent) 
{
    int x = dis(gen), y = dis(gen);
    while (opponent.getBoard().getCell(x, y).state == HIT || opponent.getBoard().getCell(x, y).state == MISS) 
    {
        x = dis(gen);
        y = dis(gen);
    }
    return opponent.getBoard().isHit(x, y);
}
