#include "Game.h"
#include <ctime>

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    Game game(5, 9, 100); // game(��������� ����� ������, �������� �����, �������� ����)
    game.run();
    return 0;
}