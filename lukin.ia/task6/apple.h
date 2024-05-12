#pragma once
#include "sec_func.h"
#include "game_field.h"
#include "snake.h"
using namespace std;

class Apple
{
	game_field field;
	COORD pos;
	bool is_spawned;
	void spawn(vector<COORD> vec)
	{
		srand(time(NULL));
		bool flag;
		do
		{
			flag = true;
			pos.X = 3 + rand() % (field.Get_width() - 5);
			pos.Y = 3 + rand() % (field.Get_height() - 5);
			for (COORD crd : vec)
			{
				if (crd.X == pos.X && crd.Y == pos.Y)
				{
					flag = false;
					break;
				}
			}
		} while (!flag);
	}
public:
	Apple(game_field field_) : field(field_.Get_height(), field_.Get_width()) 
	{
		is_spawned = false;
	}
	void draw(vector<COORD> vec)
	{
		if (is_spawned)
		{
			set_cursor(pos);
			cout << "%";
			return;
		}
		else if (!is_spawned)
		{
			spawn(vec);
			set_cursor(pos);
			cout << "%";
			is_spawned = true;
		}
	}
	COORD Get_Pos()
	{
		return pos;
	}
	void change_status()
	{
		is_spawned = false;
	}
};