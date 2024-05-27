#pragma once

#include "Common.h"
#include "Settings.h"
#include "Map.h"
#include "Snake.h"
#include "Food.h"
#include "Utils.h"

class Game {
private:
    Settings settings;
    Map map;
    Snake snake;
    Food food;
    bool isRunning = true;
    int score = 0;

public:
    Game() : map(settings.width, settings.height, settings.wallSymbol),
        snake(settings.width / 2, settings.height / 2, settings.snakeSymbol),
        food(1 + rand() % (settings.width - 3), 1 + rand() % (settings.height - 2),
            settings.width, settings.height, settings.foodSymbol) {}

    void updateDir();

    void updateSnake();

    void draw();

    void run();
};