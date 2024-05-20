#include "Game.h"

Game::Game()
    : humanBoard(10), computerBoard(10),
    humanPlayer(humanBoard), computerPlayer(computerBoard) {}

void Game::play() 
{
    humanPlayer.placeShips();
    computerPlayer.placeShips();

    while (!humanBoard.allShipsSunk() && !computerBoard.allShipsSunk()) 
    {
        if (humanPlayer.takeTurn(computerPlayer)) 
        {
            std::cout << "You hit a ship!\n";
        }
        else 
        {
            std::cout << "You missed.\n";
        }
        if (computerPlayer.takeTurn(humanPlayer)) 
        {
            std::cout << "Computer hit your ship!\n";
        }
        else 
        {
            std::cout << "Computer missed.\n";
        }
    }

    if (humanBoard.allShipsSunk()) 
    {
        std::cout << "Computer wins!\n";
    }
    else 
    {
        std::cout << "You win!\n";
    }
}
