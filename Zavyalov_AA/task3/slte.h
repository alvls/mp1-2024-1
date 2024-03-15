#pragma once
#include <limits>
#include <Windows.h>
#include <string>
#include <iostream>

using namespace std;

class slte { // single-line text editor
	unsigned int size; // size of input field
	COORD position; // coordinates of input field
	string input_value; // user input
	
public:
	slte(int size_, COORD position_ = {0, 0}) {
		size = size_, position = position_;
	}
	slte() {};
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
	void setInput() {
		char* buffer = new char[size+1];
		cin.get(buffer, size+1);
		input_value = buffer;
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		delete[] buffer;
	}
	string getInput() {
		return input_value;
	}
};