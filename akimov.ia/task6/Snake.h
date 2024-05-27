#ifndef SNAKE_H
#define SNAKE_H

#include "GameObject.h"
#include "Field.h"
#include <deque>

using namespace std;

enum Direction { UP, DOWN, LEFT, RIGHT };

class Snake : public GameObject
{
    deque<pair<int, int>> body;
    Direction direction;
    Field* field;
    int growToLength;
    bool isAlive;
    bool isWin;
public:
    Snake(Field* fld, int length, int growLength);
    void changeDirection(Direction newDirection);
    void update() override;
    void draw() override;
    bool alive() const;
    bool win() const;
};

#endif