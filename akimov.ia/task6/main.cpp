#include "Game.h"
#include <ctime>

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    Game game(5, 9, 100); // game(начальная длина змейки, победная длина, скорость игры)
    game.run();
    return 0;
}