#pragma once

#include "Common.h"

class Map {
public:
    int width, height;
    char symbol;
    vector<vector<char>> grid;

    Map(int w, int h, char symbol_) : width(w), height(h), symbol(symbol_), grid(h, vector<char>(w, ' ')) {
        for (int i = 0; i < width; i++) {
            grid[0][i] = symbol;
            grid[height - 1][i] = symbol;
        }
        for (int i = 0; i < height; i++) {
            grid[i][0] = symbol;
            grid[i][width - 1] = symbol;
        }
    }

    void display();
};