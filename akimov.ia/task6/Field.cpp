#include "Field.h"
#include "Snake.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

using namespace std;

Field::Field() : grid(N + 2, vector<int>(M + 2, 0))
{
    for (int i = 0; i < N + 2; ++i)
    {
        grid[i][0] = WALL;
        grid[i][M + 1] = WALL;
    }
    for (int j = 0; j < M + 2; ++j)
    {
        grid[0][j] = WALL;
        grid[N + 1][j] = WALL;
    }
}

void Field::placeFood()
{
    int x, y;
    do
    {
        x = 1 + rand() % N;
        y = 1 + rand() % M;
    } while (grid[x][y] != 0);
    grid[x][y] = FOOD;
}

void Field::setCell(int x, int y, int value)
{
    grid[x][y] = value;
}

int Field::getCell(int x, int y) const
{
    return grid[x][y];
}

void Field::update()
{
    // Поле само по себе не обновляется, его обновляют другие объекты
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Field::draw()
{
    for (int i = 0; i < N + 2; ++i)
    {
        for (int j = 0; j < M + 2; ++j)
        {
            if (grid[i][j] == WALL)
            {
                setColor(FOREGROUND_RED);
                cout << "#";
            }
            else if (grid[i][j] == FOOD)
            {
                setColor(FOREGROUND_GREEN);
                cout << "*";
            }
            else if (grid[i][j] > 0)
            {
                if (grid[i][j] == 1)
                {
                    setColor(FOREGROUND_BLUE);
                    cout << "X"; // Голова змейки
                }
                else
                {
                    setColor(FOREGROUND_RED | FOREGROUND_BLUE);
                    cout << "o"; // Тело змейки
                }
            }
            else
                cout << " ";
        }
        cout << endl;
    }
}