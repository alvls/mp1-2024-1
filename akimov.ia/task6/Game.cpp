#include "Game.h"
#include <conio.h>
#include <iostream>
#include <windows.h>

using namespace std;

Game::Game(int initialLength, int growLength, int spd) : snake(&field, initialLength, growLength), speed(spd)
{
    field.placeFood();
}

void Game::run()
{
    while (snake.alive())
    {
        if (_kbhit())
            switch (_getch())
            {
            case 72:
                snake.changeDirection(UP);
                break;
            case 80:
                snake.changeDirection(DOWN);
                break;
            case 75:
                snake.changeDirection(LEFT);
                break;
            case 77:
                snake.changeDirection(RIGHT);
                break;
            }
        snake.update();
        system("cls");
        snake.draw();
        Sleep(speed);
        if (!snake.alive())
        {
            if (snake.win())
                cout << "You win!" << endl;
            else
                cout << "Game Over!" << endl;
            system("pause");
        }
    }
}