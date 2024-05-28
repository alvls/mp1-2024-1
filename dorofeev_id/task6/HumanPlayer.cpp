#include "HumanPlayer.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <limits>


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
            std::string startCoord, endCoord;
            iss >> startCoord >> endCoord;

            if (startCoord.length() < 2 || endCoord.length() < 2)
            {
                std::cout << "Invalid input format. Please enter coordinates in the format: A1 A4 or B2 E2.\n";
                continue;
            }

            char startCol = startCoord[0], endCol = endCoord[0];
            int startRow, endRow;
            try {
                startRow = std::stoi(startCoord.substr(1));
                endRow = std::stoi(endCoord.substr(1));
            }
            catch (const std::invalid_argument&) {
                std::cout << "Invalid row input. Please enter valid coordinates.\n";
                continue;
            }

            if (!isalpha(startCol) || !isalpha(endCol))
            {
                std::cout << "Invalid column input. Please enter valid coordinates.\n";
                continue;
            }

            startCol = toupper(startCol);
            endCol = toupper(endCol);

            int x1 = startRow - 1, y1 = startCol - 'A';
            int x2 = endRow - 1, y2 = endCol - 'A';

            if (x1 < 0 || x1 >= BOARD_SIZE || y1 < 0 || y1 >= BOARD_SIZE ||
                x2 < 0 || x2 >= BOARD_SIZE || y2 < 0 || y2 >= BOARD_SIZE)
            {
                std::cout << "Coordinates out of bounds. Please try again.\n";
                continue;
            }

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
    std::istringstream iss(input);
    std::string coord;
    iss >> coord;

    if (coord.length() < 2)
    {
        std::cout << "Invalid input format. Please enter coordinates in the format: A1.\n";
        return false;
    }

    char col = coord[0];
    int row;
    try {
        row = std::stoi(coord.substr(1));
    }
    catch (const std::invalid_argument&) {
        std::cout << "Invalid row input. Please enter valid coordinates.\n";
        return false;
    }

    if (!isalpha(col))
    {
        std::cout << "Invalid column input. Please enter valid coordinates.\n";
        return false;
    }

    col = toupper(col);

    int x = row - 1, y = col - 'A';

    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
    {
        std::cout << "Coordinates out of bounds. Please try again.\n";
        return false;
    }

    return opponent.getBoard().isHit(x, y);
}
