#include "HumanPlayer.h"
#include <iostream>
#include <sstream>

HumanPlayer::HumanPlayer(Board& board) : Player(board) {}

void HumanPlayer::placeShips() 
{
    int shipSizes[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
    for (int size : shipSizes) 
    {
        bool placed = false;
        while (!placed) 
        {
            board.display();
            std::cout << "Place a ship of size " << size << ".\n";
            std::cout << "Enter the starting and ending coordinates (e.g., A1 A4 or B2 E2): ";
            std::string input;
            std::getline(std::cin, input);
            std::istringstream iss(input);
            char startCol, endCol;
            int startRow, endRow;
            iss >> startCol >> startRow >> endCol >> endRow;
            int x1 = startRow - 1, y1 = startCol - 'A';
            int x2 = endRow - 1, y2 = endCol - 'A';
            if (board.placeShip(x1, y1, x2, y2, size)) 
            {
                placed = true;
            }
            else 
            {
                std::cout << "Invalid placement. Try again.\n";
            }
        }
    }
}

bool HumanPlayer::takeTurn(Player& opponent) 
{
    board.display();
    std::cout << "Enter coordinates to hit (e.g., A1): ";
    std::string input;
    std::getline(std::cin, input);
    char col;
    int row;
    std::istringstream iss(input);
    iss >> col >> row;
    int x = row - 1, y = col - 'A';
    return opponent.getBoard().isHit(x, y);
}
