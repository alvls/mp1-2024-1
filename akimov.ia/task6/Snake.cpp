#include "Snake.h"
#include <iostream>
#include <cstdlib>

Snake::Snake(Field* fld, int length, int growLength) : field(fld), direction(LEFT), growToLength(growLength), isAlive(true), isWin(false)
{
    int startX = 1 + rand() % (N - 5);
    int startY = 1 + rand() % (M - 5);
    for (int i = 0; i < length; ++i)
    {
        body.emplace_back(startX, startY + i);
        field->setCell(startX, startY + i, i == 0 ? 1 : 2); // 1 для головы, 2 для тела
    }
}

void Snake::changeDirection(Direction newDirection)
{
    if ((direction == UP && newDirection == DOWN) || (direction == DOWN && newDirection == UP) ||
        (direction == LEFT && newDirection == RIGHT) || (direction == RIGHT && newDirection == LEFT))
        return;
    direction = newDirection;
}

void Snake::update()
{
    if (!isAlive)
        return;
    int dx = 0, dy = 0;
    switch (direction)
    {
    case UP:
        dx = -1;
        break;
    case DOWN:
        dx = 1;
        break;
    case LEFT:
        dy = -1;
        break;
    case RIGHT:
        dy = 1;
        break;
    }
    int newX = body.front().first + dx;
    int newY = body.front().second + dy;
    if (field->getCell(newX, newY) == WALL || field->getCell(newX, newY) > 0)
    {
        isAlive = false;
        return;
    }
    bool grow = (field->getCell(newX, newY) == FOOD);
    body.push_front({ newX, newY });
    field->setCell(newX, newY, 1); // Устанавливаем голову
    if (!grow)
    {
        int tailX = body.back().first;
        int tailY = body.back().second;
        field->setCell(tailX, tailY, 0); // Очищаем хвост
        body.pop_back();
    }
    else
        field->placeFood();
    // Обновляем тело змейки
    if (body.size() > 1)
        field->setCell(body[1].first, body[1].second, 2);
    if (body.size() == growToLength)
    {
        isWin = true;
        isAlive = false;
    }
}

void Snake::draw()
{
    field->draw();
}

bool Snake::alive() const
{
    return isAlive;
}

bool Snake::win() const
{
    return isWin;
}