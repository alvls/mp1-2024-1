#include "Board.h"

Board::Board(int size) : size(size), grid(size, std::vector<Cell>(size)) {}

void Board::display() const 
{
    std::cout << "  A B C D E F G H I J\n";
    for (int i = 0; i < size; ++i) 
    {
        std::cout << i + 1 << ' ';
        for (int j = 0; j < size; ++j) 
        {
            char c = '.';
            switch (grid[i][j].state) 
            {
            case EMPTY: c = '.'; break;
            case SHIP: c = 'S'; break;
            case HIT: c = 'X'; break;
            case MISS: c = 'O'; break;
            }
            std::cout << c << ' ';
        }
        std::cout << '\n';
    }
}

bool Board::placeShip(int x1, int y1, int x2, int y2, int size) 
{
    if (x1 != x2 && y1 != y2) return false;
    if (std::abs(x2 - x1) + 1 != size && std::abs(y2 - y1) + 1 != size) return false;

    for (int i = x1; i <= x2; ++i) 
    {
        for (int j = y1; j <= y2; ++j) 
        {
            if (grid[i][j].state != EMPTY || isAdjacent(i, j, i, j)) return false;
        }
    }

    for (int i = x1; i <= x2; ++i) 
    {
        for (int j = y1; j <= y2; ++j) 
        {
            grid[i][j].state = SHIP;
        }
    }
    return true;
}

bool Board::isHit(int x, int y) 
{
    if (grid[x][y].state == SHIP) 
    {
        grid[x][y].state = HIT;
        return true;
    }
    else 
    {
        grid[x][y].state = MISS;
        return false;
    }
}

bool Board::allShipsSunk() const 
{
    for (const auto& row : grid) 
    {
        for (const auto& cell : row) 
        {
            if (cell.state == SHIP) return false;
        }
    }
    return true;
}

Cell Board::getCell(int x, int y) const 
{
    return grid[x][y];
}

bool Board::isAdjacent(int x1, int y1, int x2, int y2) const 
{
    for (int i = -1; i <= 1; ++i) 
    {
        for (int j = -1; j <= 1; ++j) 
        {
            int x = x1 + i;
            int y = y1 + j;
            if (x >= 0 && x < size && y >= 0 && y < size && !(x == x2 && y == y2)) 
            {
                if (grid[x][y].state == SHIP) 
                {
                    return true;
                }
            }
        }
    }
    return false;
}
