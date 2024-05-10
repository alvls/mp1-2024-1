#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
class Snake
{
	COORD head;
	std::vector<COORD> body;
public:

};

class Field
{
	short height; // height
	short width; // width
public:
	Field(short n, short m): height(n), width(m) {}
	void Show() {
		SetConsoleTextAttribute(hConsole, 15); // 15 = white
		for (short i = 0; i < width + 2; i++) {
			COORD pos = { i, 0 };
			SetConsoleCursorPosition(hConsole, pos);
			std::cout << char(219);
			pos = { i, short(height + 1)};
			SetConsoleCursorPosition(hConsole, pos);
			std::cout << char(219);
		}
		for (short i = 1; i < height + 1; i++) {
			COORD pos = { 0, i };
			SetConsoleCursorPosition(hConsole, pos);
			std::cout << char(219);
			pos = { short(width + 1) , i };
			SetConsoleCursorPosition(hConsole, pos);
			std::cout << char(219);
		}
	}
	void Hide() {
		for (short i = 0; i < width + 2; i++) {
			COORD pos = { i, 0 };
			SetConsoleCursorPosition(hConsole, pos);
			std::cout << char(32);
			pos = { i, short(height + 1) };
			SetConsoleCursorPosition(hConsole, pos);
			std::cout << char(32);
		}
		for (short i = 1; i < height + 1; i++) {
			COORD pos = { 0, i };
			SetConsoleCursorPosition(hConsole, pos);
			std::cout << char(32);
			pos = { short(width + 1), i };
			SetConsoleCursorPosition(hConsole, pos);
			std::cout << char(32);
		}
	}
};

class Food
{
	COORD position;
public:
	Food(COORD pos) {
		position = pos;
	}
	void Show(int color = 12) {
		SetConsoleCursorPosition(hConsole, position);
		SetConsoleTextAttribute(hConsole, color);
		std::cout << char(219);
	}
	void Hide() {
		SetConsoleCursorPosition(hConsole, position);
		std::cout << char(32);
	}

};

class SnakeGame
{

};