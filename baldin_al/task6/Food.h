#pragma once

#include "Common.h"
#include "Snake.h"

class Food {
public:
    point position;
    char symbol;
    int width;
    int height;

    Food(int x_, int y_, int width_, int height_, char symbol_) : position(x_, y_), symbol(symbol_), width(width_), height(height_) {}

    void relocate(int width, int height, const Snake& snake);
};