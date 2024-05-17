#include <iostream>
#include <vector>
#include <ctime>
#include <conio.h>
#include <Windows.h>

using namespace std;

class Field
{
public:
    int width; // ширина поля
    int height; // высота поля
    char** cells; // массив клеток

    // ---------------------------------------------------------------------------------

    Field(int width2, int height2) // конструктор-инициализатор
    {
        width = width2 + 2; // добавление стен
        height = height2 + 2; // добавление стен
        // выделение памяти под двумерный массив
        cells = new char* [height];
        for (int i = 0; i < height; i++)
            cells[i] = new char[width]; // выделение памяти под новый одномерный массив
        // инициализация всех клеток пустыми
        memset(cells[0], '#', width); // верхняя граница
        for (int i = 1; i < height - 1; i++)
        {
            memset(cells[i], ' ', width); // заполнение пробелами
            cells[i][0] = '#'; // левая граница
            cells[i][width - 1] = '#'; // правая граница
        }
        memset(cells[height - 1], '#', width); // нижняя граница
    }

    ~Field() // деструктор
    {
        // освобождение памяти от двумерного массива
        for (int i = 0; i < height; i++)
            delete[] cells[i];
        delete[] cells;
    }

};

enum Direction {LEFT, RIGHT, UP, DOWN }; // перечисление направлений движения

class Snake
{
public:
    int length; // длина змейки
    Direction direction = LEFT; // направление движения змейки
    vector<pair<int, int>> body; // вектор координат всех сегментов тела змейки (включая голову)
    int speed; // скорость змейки

    // ---------------------------------------------------------------------------------

    Snake(int startX, int startY, int speed2) : length(5), direction(LEFT), speed(speed2) // конструктор-инициализатор
    {
        for (int i = 0; i < 5; i++) // заполняем вектор snake начальными координатами 5 сегментов змейки
            body.push_back({ startX + i, startY }); // "хвост" расположен справа от "головы"
    }

    bool isInsideBody(int x, int y) // функция, проверяющая нахождение заданной точки внутри змейки
    {
        for (const auto& segment : body)  // range-based цикл для прохода по контейнеру vector
            if (segment.first == x && segment.second == y)
                return true;
        return false;
    }

    void move() // функция, обновляющая позицию змейки
    {
        int newX = body[0].first;
        int newY = body[0].second;
        switch (direction) // изменяем координаты головы змейки в соответствии с направлением
        {
        case LEFT:
            newX--;
            break;
        case RIGHT:
            newX++;
            break;
        case UP:
            newY--;
            break;
        case DOWN:
            newY++;
            break;
        default:
            break;
        }

        for (int i = length - 1; i > 0; i--) // сдвигаем все сегменты тела змейки, кроме головы
            body[i] = body[i - 1];
        body[0] = pair<int, int>(newX, newY); // обновление позиции головы змейки

    }

    bool checkCollision(const Field& field) // функция, проверяющая столкновение змейки с самой собой или стенами
    {
        int headX = body[0].first;
        int headY = body[0].second;
        if (headX < 1 || headX >= field.width - 1 || headY < 1 || headY >= field.height - 1) // проверка на столкновение со стенами
            return true;
        for (int i = 1; i < length; i++)
            if (headX == body[i].first && headY == body[i].second) // проверка на столкновение змейки с самой собой
                return true;
        return false;
    }

    void grow() // функция, увеличивающая длину змейки
    {
        body.push_back(body.back()); // добавляем новый сегмент в конец тела змейки
        length++;
    }
};

class Food
{
public:
    int fruitX;
    int fruitY;

    // ---------------------------------------------------------------------------------

    Food(int fruitX2, int fruitY2) : fruitX(fruitX2), fruitY(fruitY2) {}
};


class Game
{
private:
    Field field;
    Snake snake;
    Food food;
    bool gameOver = false; // флаг об окончании игры
    int winLength; // длина змейки для выигрыша
public:
    Game(int width2, int height2, int startX2, int startY2, int speed2,int fruitX2, int fruitY2, int winLength2) : field(width2, height2), snake(startX2, startY2, speed2), food(fruitX2, fruitY2), winLength(winLength2) {} // конструктор-инициализатор

    void draw() // функция, выводящая в консоль игровое поле, змейку и фрукты
    {
        system("cls"); // очистка консоли
        for (int i = 0; i < field.height; i++) 
        {
            for (int j = 0; j < field.width; j++)
            {
                bool isSnake = false; // флаг: клетка внутри змейки
                bool isHead = false; // флаг : клетка - голова змейки
                for (const auto& segment : snake.body) // range-based цикл для прохода по контейнеру vector
                {
                    if (segment.first == j && segment.second == i)
                    {
                        isSnake = true;
                        if (segment.first == snake.body[0].first && segment.second == snake.body[0].second)
                            isHead = true;
                        break;
                    }
                }
                bool isFruit = false; // флаг : клетка - фрукт
                if (food.fruitX == j && food.fruitY == i)
                    isFruit = true;
                // вывод в консоль и окраска символов
                if (isSnake && isHead)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY); // Цвет головы (синий)
                    cout << 'O'; // символ для тела змейки
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Сброс цвета
                }
                else if (isSnake)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);  // Цвет тела (голубой)
                    cout << 'O'; // символ для тела змейки
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Сброс цвета
                }
                else if (isFruit)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Цвет фрукта (зелёный)
                    cout << '@'; // символ для фрукта
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // сброс цвета
                }
                else
                    cout << field.cells[i][j];
            }
            cout << endl;
        }
    }

    void Input() // функция, считывающая нажатия клавиш
    {
        if (_kbhit()) // если клавиша нажата
        {
            char key = _getch(); // что за клавиша нажата
            switch (key)
            {
            case 'w': // "стрелка" вверх
                if (snake.direction != DOWN)
                    snake.direction = UP;
                break;
            case 's': // "стрелка" вниз
                if (snake.direction != UP)
                    snake.direction = DOWN;
                break;
            case 'a': // "стрелка" влево
                if (snake.direction != RIGHT)
                    snake.direction = LEFT;
                break;
            case 'd': // "стрелка" вправо
                if (snake.direction != LEFT)
                    snake.direction = RIGHT;
                break;
            }
        }
    }

    void update() //  функция, обновляющая состояние игры
    {
        snake.move();
        if (snake.body[0].first == food.fruitX && snake.body[0].second == food.fruitY) // если змейка съела фрукт
        {
            snake.grow();
            do {
                food.fruitX = rand() % (field.width - 2) + 1;
                food.fruitY = rand() % (field.height - 2) + 1;
            } while (snake.isInsideBody(foodX, foodY)); // пока фрукт спавнится внутри змейки
        }
    }

    void gameplay() // функция, осуществляющая основной игровой процесс
    {
        while (!gameOver)
        {
            Input();
            update();
            draw();
            if (snake.checkCollision(field)) // проверка на конец игры (значение переменной gameOver)
            {
                gameOver = true;
                cout << "Snake length: " << snake.length << endl;
                cout << "YOU HAVE LOST !" << endl;
            }
            if (snake.length >= winLength)
            {
                gameOver = true;
                cout << "Snake length: " << snake.length << endl;
                cout << "YOU HAVE WON !" << endl;
            }
            Sleep(snake.speed); // приостанавливает выполнение текущего потока (иллюзия скорости)
        }
    }
};

int main() {

    srand(time(NULL)); // инициализация генератора случайных чисел
    int M = 60;
    int N = 20;
    int headX = rand() % (M - 4) + 1; // ограничение для спавна змейки
    if (headX < 5)
        headX = 5; // запас перед левой границей поля (для более комфортного геймплея)
    int headY = rand() % N + 1;
    int foodX, foodY;
    int snake_speed = 100;
    int win = 20; // длина змейки для победы
    Snake snake(headX, headY, snake_speed); // объект типа snake (нужен для правильной генерации первого фрукта)
    do {
        foodX = rand() % M + 1;
        foodY = rand() % N + 1;
    } while (snake.isInsideBody(foodX, foodY));
    Game game(M, N, headX, headY, snake_speed, foodX, foodY, win);
    game.gameplay();
    return 0;
}


