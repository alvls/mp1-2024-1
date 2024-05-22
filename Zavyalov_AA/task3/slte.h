#pragma once
#include <limits>
#include <Windows.h>
#include <string>
#include <iostream>
#include <conio.h>

#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_BACKSPACE 8
#define KB_ENTER 13

using namespace std;

class slte { // single-line text editor
	unsigned int size; // size of input field
	COORD position; // coordinates of input field
	string input_value; // user input
	
public:
	slte(int size_ = 300, COORD position_ = {0, 0}) {
		size = size_, position = position_;
	}
	void setSize(unsigned int size_) {
		size = size_;
	}
	unsigned int getSize() {
		return size;
	}
	void setPosition(COORD position_) {
		position = position_;
	}
	void setPosition(short x, short y) {
		position = { x, y };
	}
	COORD getPosition() {
		return position;
	}
	void locate() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
	}
	void start() {
		locate();
		char c;
		short dx = 0;
		COORD curpos = position;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		while (true) {
			c = _getch();
			if (c == KB_BACKSPACE) {
				SetConsoleCursorPosition(hConsole, curpos);
				dx = max(0, dx - 1);
				input_value.erase(dx);

				curpos.X = max(curpos.X - 1, position.X);
				cout << " ";
				continue;
			}
			if (c == KB_ENTER) {
				break;
			}
			if (c == -32) {
				c = _getch();
				switch (c)
				{
				case KB_LEFT:
					dx = max(0, dx - 1);
					curpos.X = max(curpos.X - 1, position.X);
					break;
				case KB_RIGHT:
					curpos.X = min(curpos.X + 1, position.X + size);
					dx = min(size, dx + 1);
				default:
					break;
				}
				SetConsoleCursorPosition(hConsole, curpos);
			}
			else
			{
				curpos.X = min(curpos.X + 1, position.X + size);
				dx = min(size, dx + 1);
				SetConsoleCursorPosition(hConsole, curpos);
				cout << c;
				if (input_value.length() < dx) {
					input_value += char(c);
				}
				else
				{
					input_value[dx - 1] = char(c);
				}
			}
		}
	}
	string getInput() {
		return input_value;
	}
};