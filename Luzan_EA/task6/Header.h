#pragma once
#include<iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>

//можно упротить, если хранить bcp_dir как поле
// переделать рандом
// покраску во внутрь
// почистить
// придумать что-то с этой консолью, её слишком много
	//исключения
//установка сложности

// дружественные для двух классов??
typedef unsigned ui;
typedef std::pair<unsigned, unsigned> pui;

enum TColor {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
	DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
	LIGHTMAGENTA, YELLOW, WHITE
};

enum TButtons {
	ARROW_UP = 72, ARROW_DOWN = 80, ARROW_RIGHT = 77, ARROW_LEFT = 75, ENTER = 13
};

const char WALL_CHAR = '#';
const char EMPTY_CHAR = 'e';
const char HEAD_CHAR = 'O';
const char BODY_CHAR = 'o';
const char FOOD_CHAR = '^';

class Snake {
private:
	std::vector <std::pair<unsigned, unsigned>> snake_coords; // 0 is head 
	char head, body;
public:
	Snake() :head(HEAD_CHAR), body(BODY_CHAR) { }

	Snake(const Snake& s) = default;

	~Snake() = default;

	void AddCoordinationsPair(const ui x, const ui y) {
		snake_coords.push_back(std::make_pair(x, y));
	}

	void AddCoordinationsPair(const pui x) {
		snake_coords.push_back(x);
	}
	
	auto GetHeadCoordinations() {
		return snake_coords[0];
	}

	auto GetSnakeCoordinations() {
		return snake_coords;
	}

	unsigned GetSnakeLen() {
		return snake_coords.size();
	}

	bool CheckHeadCollision(const pui cell) {
		for (int i = 1; i < snake_coords.size(); i++)
			if (cell == snake_coords[i])
				return true;
		return false;
	}

	bool CheckCollision(const pui cell) {
		for (int i = 0; i < snake_coords.size(); i++)
			if (cell == snake_coords[i])
				return true;
		return false;
	}

	void drawSnake(const ui zero_x, const ui zero_y) {
		HANDLE Console;
		Console = GetStdHandle(STD_OUTPUT_HANDLE);
		if (Console == 0)
			throw "CONSOLE HAVE NOT FOUND";
		COORD pos{ zero_x + 1, zero_y + 1};

		pos.X += snake_coords[0].first;
		pos.Y += snake_coords[0].second;
		SetConsoleCursorPosition(Console, pos);

		CONSOLE_SCREEN_BUFFER_INFO buf;
		GetConsoleScreenBufferInfo(Console, &buf);
		SetConsoleTextAttribute(Console, (RED)); // << 4 - 4 бита влево, цветов 16 = 2 ^ 4 
		std::cout << head; 
		SetConsoleTextAttribute(Console, (GREEN));

		for (ui i = 1; i < snake_coords.size(); i++) {
			pos.X = zero_x + 1 + snake_coords[i].first;
			pos.Y = zero_y + 1 + snake_coords[i].second;
			SetConsoleCursorPosition(Console, pos);
			std::cout << body;
		}
		SetConsoleTextAttribute(Console, buf.wAttributes);

	}
	
	bool PotentialMove(const char dir, pui& move) {
		pui hcell = snake_coords[0];
		switch (dir) {
		case ARROW_DOWN:
			move.first = hcell.first;
			move.second = hcell.second + 1;
			break;
		case ARROW_UP:
			move.first = hcell.first;
			move.second = hcell.second - 1;
			break;
		case ARROW_LEFT:
			move.first = hcell.first - 1;
			move.second = hcell.second;
			break;
		case ARROW_RIGHT:
			move.first = hcell.first + 1;
			move.second = hcell.second;
			break;
		default:
			return false;
		}
		if (snake_coords.size() > 1)
			return (move == snake_coords[1]) ? false : true;

		return true;
	}

	void Move(const pui move) {
		for (int i = snake_coords.size() - 2; i >= 0; i--) {
			snake_coords[i + 1] = snake_coords[i];
		}
		snake_coords[0] = move;
	}

	void Eat(const pui move) {
		pui tmp = snake_coords[snake_coords.size() - 1];
		Move(move);
		snake_coords.push_back(tmp);
	}
};

class EmptyField {
protected:
	char* con_field;
	char empty;
	char wall;
	unsigned width;
	unsigned height;

public:
	EmptyField(const unsigned width_, const unsigned height_)
		: width(width_), height(height_), empty(EMPTY_CHAR), wall(WALL_CHAR) {
		ui size_ = (width) * (height);
		con_field = new char[size_];
		for (int i = 0; i < size_;  i++)
			con_field[i] = empty;
	}

	ui GetWidth() {
		return width;
	}

	ui GetHeight() {
		return height;
	}

	~EmptyField() {
		delete[] con_field;
	}

	bool CheckCollision(const pui cell, const ui zero_x, const ui zero_y) {
		if ( (cell.first >= width) || (cell.first < 0) )
			return true;
		if ((cell.second >= height) || (cell.second < 0))
			return true;
		return false;
	}

	// вот это всё в класс "поле" бы 
	void drawField(ui zero_x = 1, ui zero_y = 1) {
		ui sz = width * height;
		std::string tab = "", space = "";
		for (int i = 0; i < zero_x; i++)
			tab += ' ';
		for (int i = 0; i < width; i++)
			space += ' ';

		//вывод в консоль:
		for (int i = 0; i < zero_y; i++)
			std::cout << std::endl;
		std::cout << tab;
		for (int i = 0; i < width+2; i++)
			std::cout << wall;

		std::cout << std::endl;
		for (int i = 0; i < height; i++)
			std::cout << tab << wall << space << wall << std::endl;

		std::cout << tab;
		for (int i = 0; i < width+2; i++)
			std::cout << wall;
		std::cout << std::endl;
	}
};

class Game {
private:
	pui food_pos;
	Snake snake;
	EmptyField field;

public:
	Game(const ui width_, const ui height_, ui start_snake_len)
		: field(width_, height_), snake(){
		if (width_ - start_snake_len < 3)
			throw "FIELD IS LESS THAN SNAKE";
		if ((width_ < 5) || (height_ < 3))
			throw "FIELD IS VERY SMALL";
		ui middle = ((width_ - start_snake_len) / 2) - ((width_ - start_snake_len + 1) % 2);
			//(width_ + 1) % 2 - cvещает на 1 влево, если ширина чётная (левая клетка середины, которая пара клеток)
			// eg: 6/2 = 3, 012!3!45 - (7%2 == 1) -> 01!2!345
		for (int i = 0; i < start_snake_len; i++)
			snake.AddCoordinationsPair(std::make_pair(middle++, height_ / 2 + height_%2));
		
		GenFood();
	}

	~Game() {}

	void DrawField(const ui zero_x = 1, const ui zero_y = 1) { 
		COORD pos{0, 0};
		CONSOLE_SCREEN_BUFFER_INFO buf;
		HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
		if (Console == 0)
			throw "CONSOLE HAVE NOT FOUND";
		GetConsoleScreenBufferInfo(Console, &buf);
		
		//SetConsoleTextAttribute(Console, (BROWN << 4) | BROWN);
		SetConsoleCursorPosition(Console, pos);
		field.drawField(zero_x, zero_y);
		
		pos.X = 0;
		pos.Y = 0;
		SetConsoleCursorPosition(Console, pos);
		snake.drawSnake(zero_x, zero_y);

		SetConsoleTextAttribute(Console, (LIGHTGREEN << 4) | BLACK);
		pos.X = zero_x + 1 + food_pos.first;
		pos.Y = zero_y + 1 + food_pos.second;
		SetConsoleCursorPosition(Console, pos);
		DrawFood();

		pos.X = zero_x;
		pos.Y = zero_y + field.GetHeight() + 2 + 1;
		SetConsoleTextAttribute(Console, buf.wAttributes);
		SetConsoleCursorPosition(Console, pos);
	}

	bool play(const ui zero_x = 1, const ui zero_y = 1, ui dif = 1) {
		//ui speed - divider for sleep()
		char dir = ARROW_LEFT, bcp_dir;
		pui move, bcp_move;
		bool movable = true;
		ui score = 0;

		snake.PotentialMove(dir, move);
		DrawField(zero_x, zero_y);
		std::cout << "Press any key to start";
		_getch();
		while ((!field.CheckCollision(move, zero_x, zero_y)) && (!snake.CheckHeadCollision(move))) {
			if (move == food_pos) { 
				snake.Eat(move);
				score += 10;
				GenFood();
			}
			else {
				snake.Move(move);
			}
			DrawField(zero_x, zero_y);
			std::cout << "Score: " << score << "                    ";
			Sleep(1000 / dif);
			bcp_dir = dir;
			while (_kbhit()) {
				if ((_getch() == 0xE0) && (_kbhit())) {
					dir = _getch();
					while (_kbhit()) { _getch(); }
				}
			}

			//можно упротить, если хранить bcp_dir как поле
			bcp_move = move;
			if (!snake.PotentialMove(dir, move)) {
				move = bcp_move;
				dir = bcp_dir;
			}

			snake.PotentialMove(dir, move);
		}
		Sleep(500);
		COORD pos{ 0, 0 };
		HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
		if (Console == 0)
			throw "CONSOLE HAVE NOT FOUND";
		SetConsoleCursorPosition(Console, pos);

		for (int i = 0; i < field.GetHeight() + zero_y + 2; i++) {
			for (int j = 0; j < field.GetWidth() + zero_x + 2; j++)
				std::cout << ' ';
			std::cout << std::endl;
		}
		std::cout << "YOUR SCORE: " << score << std::endl;
		return true;
	}

	pui GenFood() {
		do {
			food_pos = std::make_pair(rand() % field.GetWidth(), rand() % field.GetHeight());
		} while (snake.CheckCollision(food_pos));
		return food_pos;
	}

	pui GenFood(ui width, ui height) {
		do {
			food_pos = std::make_pair(rand() % width, rand() % height);
		} while (snake.CheckCollision(food_pos));
		return food_pos;
	}

	void DrawFood() {
		std::cout << FOOD_CHAR;
	}
};


