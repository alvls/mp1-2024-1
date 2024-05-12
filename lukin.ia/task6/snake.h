#pragma once
#include "sec_func.h"
#include "game_field.h"
#include "apple.h"
#define START_SIZE 5
using namespace std;

class Snake 
{
	vector<COORD> snake;
	COORD to_grow;
	string route;
	game_field field;
	Apple* food;
	void draw_tail()
	{
		set_color("blue");
		for (COORD crd : snake)
		{
			set_cursor(crd);
			cout << '$';
		}
		set_color("white");
	}
	void draw_head()
	{
		set_color("red");
		set_cursor(snake[0]);
		cout << '@';
		set_color("white");
	}
	void control()
	{
		if (GetAsyncKeyState('W'))
			if (route != "down")
				route = "up";
		if (GetAsyncKeyState('A'))
			if (route != "right")
				route = "left";
		if (GetAsyncKeyState('S'))
			if (route != "up")
				route = "down";
		if (GetAsyncKeyState('D'))
			if (route != "left")
				route = "right";
	}
	void grow()
	{
		if (snake[0].Y == food->Get_Pos().Y && snake[0].X == food->Get_Pos().X)
		{
			snake.push_back(to_grow);
			food->change_status();
		}
	}
public:
	Snake(game_field field_, Apple* food_): field(field_.Get_height(), field_.Get_width())
	{
		food = food_;
		route = "left";
		for (int i = 0; i < START_SIZE; i++)
		{
			COORD tmp = { field_.Get_width() / 2 + i,field_.Get_height() / 2 };
			snake.push_back(tmp);
		}
		to_grow.X = snake[snake.size() - 1].X + 1;
		to_grow.Y = snake[snake.size() - 1].Y;
	}
	void move()
	{
		to_grow = snake[snake.size() - 1];
		grow();
		control();
		if (route == "left")
		{
			COORD head = { snake[0].X - 1, snake[0].Y };
			snake.insert(snake.begin(), head);
			snake.pop_back();
		}
		if (route == "right")
		{
			COORD head = { snake[0].X + 1, snake[0].Y };
			snake.insert(snake.begin(), head);
			snake.pop_back();
		}
		if (route == "up")
		{
			COORD head = { snake[0].X, snake[0].Y - 1 };
			snake.insert(snake.begin(), head);
			snake.pop_back();
		}
		if (route == "down")
		{
			COORD head = { snake[0].X, snake[0].Y + 1 };
			snake.insert(snake.begin(), head);
			snake.pop_back();
		}
	}
	void draw()
	{
		draw_tail();
		draw_head();
	}
	bool bit_the_tail()
	{
		for (int i = 1; i < snake.size(); i++)
			if (snake[0].X == snake[i].X && snake[0].Y == snake[i].Y)
				return true;
		return false;
	}
	bool out_of_field()
	{
		if (snake[0].X == 0 || snake[0].X == field.Get_width() + 1 || snake[0].Y == 0 || snake[0].Y == field.Get_height() + 1)
			return true;
		return false;
	}
	int Get_length()
	{
		return snake.size();
	}
	vector<COORD> Get_Pos()
	{
		return snake;
	}
};