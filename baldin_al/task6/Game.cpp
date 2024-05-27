#include "Game.h"

void Game::updateDir() {
    if ((GetKeyState(VK_UP) & 0x8000) && snake.direction != DOWN) snake.direction = UP;
    else if ((GetKeyState(VK_LEFT) & 0x8000) && snake.direction != RIGHT) snake.direction = LEFT;
    else if ((GetKeyState(VK_DOWN) & 0x8000) && snake.direction != UP) snake.direction = DOWN;
    else if ((GetKeyState(VK_RIGHT) & 0x8000) && snake.direction != LEFT) snake.direction = RIGHT;
}

void Game::updateSnake() {
    if (snake.body[0].x == food.position.x && snake.body[0].y == food.position.y) {
        snake.grow();
        food.relocate(settings.width, settings.height, snake);
        score++;
    }

    snake.move();

    if (snake.body[0].x == 0 || snake.body[0].y == 0 || snake.body[0].x == settings.width - 1 || snake.body[0].y == settings.height - 1) {
        isRunning = false;
    }

    for (int i = 1; i < snake.body.size(); ++i) {
        if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
            isRunning = false;
            break;
        }
    }
}

void Game::draw() {
    gotoxy(0, 0);
    map.grid[food.position.y][food.position.x] = food.symbol;
    for (point p : snake.body) {
        map.grid[p.y][p.x] = snake.symbol;
    }
    for (int i = 0; i < settings.height; i++) {
        for (int j = 0; j < settings.width; j++) {
            if (map.grid[i][j] == food.symbol)
                cout << "\033[91m" << map.grid[i][j] << "\033[0m";
            else if (map.grid[i][j] == snake.symbol) {
                if (snake.body[0].x == j && snake.body[0].y == i)
                    cout << "\033[94m" << map.grid[i][j] << "\033[0m";
                else cout << "\033[92m" << map.grid[i][j] << "\033[0m";
            }
            else if (map.grid[i][j] == map.symbol)
                cout << "\033[95m" << map.grid[i][j] << "\033[0m";
            else cout << map.grid[i][j];
        }
        cout << '\n';
    }
    for (point p : snake.body) {
        map.grid[p.y][p.x] = ' ';
    }
    cout << "Счёт: " << score << '\n';
}

void Game::run() {
    double spent_time = clock();
    double time = clock();
    while (isRunning) {
        updateDir();
        if ((clock() - time) / CLOCKS_PER_SEC >= settings.snakeSpeed) {
            time = clock();
            updateSnake();
            draw();
            if (snake.body.size() == settings.MaxLenSnake) {
                cout << "Вы выиграли! Ваш счёт: " << score << '\n';
                cout << "Затраченное время: " << (clock() - spent_time) / CLOCKS_PER_SEC << '\n';
                GameResult result(settings.width, settings.height, score, (clock() - spent_time) / CLOCKS_PER_SEC, true);
                writeGameResultToFile(result);
                cout << "\nДля выхода в меню нажмите Enter" << '\n';
                while (true) {
                    if (_getch() == Enter) {
                        break;
                    }
                }
                return;
            }
        }
    }
    cout << "Игра завершена! Ваш счёт: " << score << '\n';
    cout << "Затраченное время: " << (clock() - spent_time) / CLOCKS_PER_SEC << '\n';
    GameResult result(settings.width, settings.height, score, (clock() - spent_time) / CLOCKS_PER_SEC, false);
    writeGameResultToFile(result);
    cout << "\nДля выхода в меню нажмите Enter" << '\n';
    while (true) {
        if (_getch() == Enter) {
            break;
        }
    }
}