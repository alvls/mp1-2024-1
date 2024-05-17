#pragma once
#include<iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <limits>

//потому что max есть в windows.h, что не даёт использоватьь его для numeric_limits
#if defined(max)
#undef max
#endif

// дружественные для двух классов??
//NULL как 0 выводится? если да, то не выводить его прост при выводе
typedef unsigned ui;
typedef std::pair<unsigned, unsigned> pui;

enum TButtons {
	ARROW_UP = 72, ARROW_DOWN = 80, ARROW_RIGHT = 77, ARROW_LEFT = 75, ENTER = 13
};

class Snake {
private:
	std::vector <std::pair<unsigned, unsigned>> snake_coords; // 0 is head 
	char head, body;
public:
	Snake(const char head_, const char body_) 
		: head(head_), body(body_) {};

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
			throw "UNCATCHED ERROR: CONSOLE HAVE NOT FOUND";
		COORD pos{ zero_x, zero_y}, bcp = pos;

		pos.X += snake_coords[0].first;
		pos.Y += snake_coords[0].second;
		SetConsoleCursorPosition(Console, pos);
		std::cout << head;
		for (ui i = 1; i < snake_coords.size(); i++) {
			pos.X = zero_x + snake_coords[i].first;
			pos.Y = zero_y + snake_coords[i].second;
			SetConsoleCursorPosition(Console, pos);
			std::cout << body;
		}
	}
	
	bool PotentialMove(const char dir, pui& move) {
		pui hcell = GetHeadCoordinations();
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
			move.first = hcell.first;
			move.second = hcell.second;
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
		: width(width_), height(height_), empty('e'), wall('#') {
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
		if ( (cell.first > width) || (cell.first <= 0) )
			return true;
		int q = cell.second - 1;
		if ((cell.second > height) || (cell.second <= 0))
			return true;
		return false;
	}

	// вот это всё в класс "поле" бы 
	/*
	// а теперь это нужно вообще?
	bool SetCell(pui cell, const char sym) {
		ui x = cell.first, y = cell.second;
		if (con_field[x * width + y] != 'e')
			return false;
		con_field[x * width + y] = sym;
		return true;
	}

	// а теперь это нужно вообще?
	bool SetSnake(std::vector <pui> snk_crd) {
		for (pui itr : snk_crd) {
			// а как рисовать голову другим цветом
		}
	}
	*/

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
	Game(const ui width_, const ui height_, ui start_snake_len, const char head, const char body)
		: field(width_, height_), snake(head, body) {
		if (width_ - start_snake_len < 0)
			throw "EXCEPTION_1: FIELD IS LESS THAN SNAKE";
		if ((width_ < 6) || (height_ < 3))
			throw "VERY SMALL FIELD";

		ui middle = width_ / 2 - (width_ + 1) % 2; 
			//(width_ + 1) % 2 - cvещает на 1 влево, если ширина чётная (левая клетка середины, которая пара клеток)
			// eg: 6/2 = 3, 012!3!45 - (7%2 == 1) -> 01!2!345
		for (int i = 0; i < 5; i++)
			snake.AddCoordinationsPair(std::make_pair(middle++, height_ / 2));
		
		do {
			food_pos = std::make_pair(rand() % width_, rand() % height_);
		} while (snake.CheckCollision(food_pos));

	}

	~Game() {}

	void DrawField(const ui zero_x = 1, const ui zero_y = 1) { //add position
		COORD pos{0, 0};
		HANDLE Console;
		Console = GetStdHandle(STD_OUTPUT_HANDLE);
		if (Console == 0)
			throw "UNCATCHED ERROR: CONSOLE HAVE NOT FOUND";
		
		SetConsoleCursorPosition(Console, pos);
		field.drawField(zero_x, zero_y);

		pos.X = 0;
		pos.Y = 0;
		SetConsoleCursorPosition(Console, pos);
		snake.drawSnake(zero_x, zero_y);

		pos.X = zero_x + food_pos.first;
		pos.Y = zero_y + food_pos.second;
		SetConsoleCursorPosition(Console, pos);
		std::cout << 'F';

		//pos.X = zero_x + field.GetWidth() + 2;
		//pos.Y = zero_y + field.GetHeight() + 2;
		pos = { 0,0 };
		SetConsoleCursorPosition(Console, pos);
	}

	bool play(const ui zero_x = 1, const ui zero_y = 1) { 
		//ui speed - divider for sleep()
		char dir = ARROW_LEFT;
		pui move;
		snake.PotentialMove(dir, move);
		DrawField(zero_x, zero_y);
		_getch();
		while ((!field.CheckCollision(move, zero_x, zero_y)) && (!snake.CheckHeadCollision(move))) {
			//if not apple
				snake.Move(move);
			//if apple
				//snake.Eat(); = Move & len++;
				//food.Gen();
			DrawField(zero_x, zero_y);
			Sleep(1000);
			if (_kbhit()) {
				_getch(); /// ?!?!?!?!?!??!??!?
				dir = _getch();
			}
			snake.PotentialMove(dir, move);
		}
		std::cout << "NU VSE\n";
		return true;


	}
};


