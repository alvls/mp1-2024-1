#include "snake_game.h"
#include "objects.h"
void SnakeGame::setcur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    HANDLE  handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(handle, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &structCursorInfo);
}

void SnakeGame::gameplay()
{
    Field field(WIDTH, HEIGHT);
    Snake snake;
    Food food;
    bool IsRunning = true;
    for (int i = 0; i < snake.snake_len; ++i)
    {   
        Coord coord(WIDTH / 2 + i, HEIGHT / 2);
        snake.snake_coord.push_back(coord);
    }
    bool new_food_flag;
    srand(time(NULL));
    do
    {
        new_food_flag = true;
        food.food_coord.x = 1 + (rand() % (WIDTH - 3));
        food.food_coord.y = 1 + (rand() % (HEIGHT - 2));
        for (int i = 0; i < snake.snake_len; ++i)
        {
            if (food.food_coord == snake.snake_coord[i])
            {
                new_food_flag = false;
                break;
            }
        }
    } while (!new_food_flag);
    double time = clock();
    bool flag = false;

    while (IsRunning)
    {
        if (GetKeyState('A') & 0x8000)
        {
            if (snake.snake_direction != RIGHT)
                snake.snake_direction = LEFT;
        }
        if (GetKeyState('W') & 0x8000)
        {
            if (snake.snake_direction != DOWN)
                snake.snake_direction = UP;
        }
        if (GetKeyState('D') & 0x8000)
        {
            if (snake.snake_direction != LEFT)
                snake.snake_direction = RIGHT;
        }
        if (GetKeyState('S') & 0x8000)
        {
            if (snake.snake_direction != UP)
                snake.snake_direction = DOWN;
        }

        if ((clock() - time) / CLOCKS_PER_SEC >= SPEED)
        {
            time = clock();
            if (food.food_coord == snake.snake_coord[0])
            {
                Coord new_coord;
                new_coord.x = snake.snake_coord[snake.snake_len - 1].x + 1;
                new_coord.y = snake.snake_coord[snake.snake_len - 1].y + 1;
                snake.snake_coord.push_back(new_coord);
                snake.snake_len++;
                flag = true;
            }
            else
                flag = false;
            bool new_food_flag;
            if (flag)
            {
                do
                {
                    new_food_flag = true;
                    food.food_coord.x = 1 + (rand() % (WIDTH - 3));
                    food.food_coord.y = 1 + (rand() % (HEIGHT - 2));
                    for (int i = 0; i < snake.snake_len; ++i)
                    {
                        if (food.food_coord == snake.snake_coord[i])
                        {
                            new_food_flag = false;
                            break;
                        }
                    }
                } while (!new_food_flag);
            }
            for (int i = snake.snake_len - 2; i >= 0; --i)
            {
                snake.snake_coord[i + 1] = snake.snake_coord[i];
            }
                
            if (snake.snake_direction == LEFT)
            {
                snake.snake_coord[0].x--;
            }
            if (snake.snake_direction == UP)
            {
                snake.snake_coord[0].y--;
            }
            if (snake.snake_direction == RIGHT)
            {
                snake.snake_coord[0].x++;
            }
            if (snake.snake_direction == DOWN)
            {
                snake.snake_coord[0].y++;
            }
            if (snake.snake_coord[0].x == 0 or snake.snake_coord[0].y == 0 or snake.snake_coord[0].x == WIDTH - 2 or snake.snake_coord[0].y == HEIGHT - 1)
                IsRunning = false;
            for (int i = 1; i < snake.snake_len; ++i)
            {
                if (snake.snake_coord[0] == snake.snake_coord[i])
                {
                    IsRunning = false;
                    break;
                }
            }
            setcur(0, 0);
            std::cout << "Score: " << snake.snake_len << std::endl;
            field.field_string[food.food_coord.y * WIDTH + food.food_coord.x] = food.food_char;
            int length = 0;
            for (length; length < snake.snake_len / 2; ++length)
            {
                field.field_string[snake.snake_coord[length].y * WIDTH + snake.snake_coord[length].x] = snake.snake_char;
            }
            for (length; length < snake.snake_len; ++length)
            {
                field.field_string[snake.snake_coord[length].y * WIDTH + snake.snake_coord[length].x] = 'o';
            }
            /*for (int i = 0; i < field.field_string.length(); ++i)
            {
                if ((field.field_string[i] == snake.snake_char or field.field_string[i] == 'o') and i != (snake.snake_coord[0].y * WIDTH + snake.snake_coord[0].x))
                    std::cout << "\033[92m" << field.field_string[i] << "\033[0m";
                else if (i == snake.snake_coord[0].y * WIDTH + snake.snake_coord[0].x)
                    std::cout << "\033[93m" << field.field_string[i] << "\033[0m";
                else if (field.field_string[i] == food.food_char)
                    std::cout << "\033[96m" << field.field_string[i] << "\033[0m";
                else
                    std::cout << "\033[91m" << field.field_string[i] << "\033[0m";
            }*/
            std::cout << field.field_string;
            for (int i = 0; i < snake.snake_len; ++i)
            {
                field.field_string[snake.snake_coord[i].y * WIDTH + snake.snake_coord[i].x] = ' ';
            }
            field.field_string[food.food_coord.y * WIDTH + food.food_coord.x] = ' ';

        }
        if (snake.snake_len == MAX_LEN)
        {
            IsRunning = false;
            std::cout << "You won!";
        }
    }
}

