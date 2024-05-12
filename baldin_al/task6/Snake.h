#pragma once

#include "Common.h"

class Snake {
public:
    vector<point> body;
    int direction = LEFT;
    char symbol;

    Snake(int x_, int y_, char symbol_) {
        for (int i = 0; i < 5; i++) {
            body.push_back(point(x_ + i, y_));
        }
        symbol = symbol_;
    }

    void move();

    void grow();

    const vector<point>& getBody() const;
};