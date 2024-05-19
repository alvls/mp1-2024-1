#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <conio.h>

const int WIDTH = 40;
const int HEIGHT = 20;
const char WALL = '#';
const char SNAKE_HEAD = '@';
const char SNAKE_BODY = 'o';
const char FOOD = '*';
const int SNAKE_INITIAL_LENGTH = 5;
const int FRAME_DELAY_MS = 200;

struct Point {
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

class Field {
public:
    std::vector<std::vector<char>> field;

    Field() {
        initField();
    }

    void initField() {
        field.resize(HEIGHT, std::vector<char>(WIDTH, ' '));
        for (int i = 0; i < HEIGHT; ++i) {
            field[i][0] = field[i][WIDTH - 1] = WALL;
        }
        for (int j = 0; j < WIDTH; ++j) {
            field[0][j] = field[HEIGHT - 1][j] = WALL;
        }
    }

    void clearCell(int x, int y) {
        field[y][x] = ' ';
    }

    void setCell(int x, int y, char c) {
        field[y][x] = c;
    }

    void printField() {
        for (const auto& row : field) {
            for (const char cell : row) {
                std::cout << cell;
            }
            std::cout << "\n";
        }
    }
};

class Snake {
public:
    std::vector<Point> body;
    int direction;

    Snake() : direction(1) {
        initSnake();
    }

    void initSnake() {
        int x = WIDTH / 2;
        int y = HEIGHT / 2;
        for (int i = 0; i < SNAKE_INITIAL_LENGTH; ++i) {
            body.emplace_back(x - i, y);
        }
    }

    Point getHead() {
        return body.front();
    }

    Point getTail() {
        return body.back();
    }

    bool isOccupied(int x, int y) const {
        for (const Point& p : body) {
            if (p.x == x && p.y == y) {
                return true;
            }
        }
        return false;
    }

    void moveSnake() {
        Point newHead = body.front();
        switch (direction) {
        case 0: newHead.y--; break;
        case 1: newHead.x++; break;
        case 2: newHead.y++; break;
        case 3: newHead.x--; break;
        }

        body.insert(body.begin(), newHead);
    }

    void removeTail() {
        body.pop_back();
    }

    void changeDirection(int newDirection) {
        if (abs(newDirection - direction) != 2) {
            direction = newDirection;
        }
    }
};

class Food {
public:
    Point food;

    void generateFood(const Snake& snake) {
        int x, y;
        do {
            x = rand() % (WIDTH - 2) + 1;
            y = rand() % (HEIGHT - 2) + 1;
        } while (snake.isOccupied(x, y));
        food = Point(x, y);
    }
};

class Game {
private:
    Field field;
    Snake snake;
    Food food;
    bool gameOver = false;
    int score = 0;

public:
    Game() {
        srand(static_cast<unsigned int>(time(nullptr)));
        food.generateFood(snake);
        updateField();
    }

    void updateField() {
        for (const auto& part : snake.body) {
            field.setCell(part.x, part.y, SNAKE_BODY);
        }
        field.setCell(snake.getHead().x, snake.getHead().y, SNAKE_HEAD);
        field.setCell(food.food.x, food.food.y, FOOD);
    }

    void play() {
        while (!gameOver) {
            system("cls");

            field.printField();
            std::cout << "Score: " << score << "\n";

            if (_kbhit()) {
                char input = _getch();
                switch (input) {
                case 'w': snake.changeDirection(0); break;
                case 'd': snake.changeDirection(1); break;
                case 's': snake.changeDirection(2); break;
                case 'a': snake.changeDirection(3); break;
                case 'q': gameOver = true; break;
                }
            }

            Point newHead = snake.getHead();
            switch (snake.direction) {
            case 0: newHead.y--; break;
            case 1: newHead.x++; break;
            case 2: newHead.y++; break;
            case 3: newHead.x--; break;
            }

            if (newHead.x < 1 || newHead.x >= WIDTH - 1 || newHead.y < 1 || newHead.y >= HEIGHT - 1 || snake.isOccupied(newHead.x, newHead.y)) {
                gameOver = true;
                continue;
            }

            snake.moveSnake();
            if (newHead.x == food.food.x && newHead.y == food.food.y) {
                food.generateFood(snake);
                score++;
            }
            else {
                field.clearCell(snake.getTail().x, snake.getTail().y);
                snake.removeTail();
            }

            updateField();
            std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY_MS));
        }

        std::cout << "Game Over! Your score: " << score << "\n";
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}
