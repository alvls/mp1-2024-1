#pragma once

enum CellState 
{
    EMPTY,
    SHIP,
    HIT,
    MISS
};

class Cell {
public:
    CellState state;
    Cell();
};

