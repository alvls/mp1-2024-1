#pragma once
#include "sec_func.h"
using namespace std;
class game_field
{
	int height;
	int width;
public:
	game_field(int height_, int width_)
	{
		height = height_;
		width = width_;
	}
	void draw()
	{
		system("cls");
		string border;
		for (int i = 0; i < width + 2; i++)
			border += '#';
		string fld;
		fld += '#';
		for (int i = 1; i <= width; i++)
			fld += ' ';
		fld += '#';
		cout << border << endl;
		for (int i = 1; i <= height; i++)
			cout << fld << endl;
		cout << border << endl;
	}
	int Get_height()
	{
		return height;
	}
	int Get_width()
	{
		return width;
	}
};