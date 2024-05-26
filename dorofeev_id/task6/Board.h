#pragma once

#include <vector>
#include <iostream>
#include "Cell.h"

#define BOARD_SIZE 10 

class Board 
{
public:
    Board(int size);
    void display() const;
    bool placeShip(int x1, int y1, int x2, int y2, int size);
    bool isHit(int x, int y);
    bool allShipsSunk() const;
    Cell getCell(int x, int y) const;

private:
    int size;
    std::vector<std::vector<Cell>> grid;
    bool isAdjacent(int x1, int y1, int x2, int y2) const;
};
