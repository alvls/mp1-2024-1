#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <random>
#include <conio.h>
#include <string>
#include <time.h>

#define KB_LEFT 37
#define KB_UP 38
#define KB_RIGHT 39
#define KB_DOWN 40

extern HANDLE hConsole;

bool wait_for_key(int timeout_milliseconds, WORD& ch, int& timeleft);
void end_animation(short n, short m, char c);
bool is_restricted(COORD pos, std::vector<COORD> restricted_positions);

bool isBody(COORD nextheadpos, std::vector<COORD> body_positions);
class Snake
{
	COORD head;
	std::vector<COORD> body;
	int size = 5;
public:
	Snake() {};
	Snake(COORD headpos) : head(headpos) {}
	void Show();
	void Hide();
	bool Move(WORD direction);
	void Eat(COORD foodpos);
	COORD getHead();
	std::vector<COORD> getBody();
	int getSize();
};

class Field
{
	short height;
	short width;
public:
	Field(short n, short m): height(n), width(m) {}
	void Show();
	void Hide();
};

class Food
{
	COORD position;
public:
	Food(COORD pos): position(pos) {}
	void Show(int color);
	void Hide();
};

class SnakeGame
{
	Snake snake;
	Field field;
	short width;
	short height;
	int speed; // period between tacts in milliseconds
	int goal;
public:
	SnakeGame(short n, short m, int goal_, int speed_ = 500): field(n, m), width(m), height(n), goal(goal_), speed(speed_){}
	void Play();
};