#ifndef GAME_H
#define GAME_H

#include "Field.h"
#include "Snake.h"

class Game
{
    Field field;
    Snake snake;
    int speed;
public:
    Game(int initialLength, int growLength, int spd);
    void run();
};

#endif