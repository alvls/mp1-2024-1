#include "Snake.h"

void Snake::move() {
    for (int i = body.size() - 2; i >= 0; i--) {
        body[i + 1] = body[i];
    }

    if (direction == UP) body[0].y--;
    else if (direction == DOWN) body[0].y++;
    else if (direction == LEFT) body[0].x--;
    else if (direction == RIGHT) body[0].x++;
}

void Snake::grow() {
    point tail = body.back();
    body.push_back(tail);
}

const vector<point>& Snake::getBody() const {
    return body;
}