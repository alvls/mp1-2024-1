#include "Player.h"

Player::Player(Board& board) : board(board) {}

Board& Player::getBoard() 
{
    return board;
}
