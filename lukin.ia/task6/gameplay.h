#pragma once
#include "Windows.h"
#include "sec_func.h"
#include "snake.h"
#include "game_field.h"
#include "apple.h"
using namespace std;

bool is_game_over(Snake snake, int len)
{
	if (snake.bit_the_tail())
		return true;
	if (snake.out_of_field())
		return true;
	if (snake.Get_length() == len)
		return true;
	return false;
}
void draw_score(int score, int target, game_field field)
{
	set_cursor({ 0,static_cast<short>(field.Get_height() + 2) });
	cout << "Your score: " << score << "    " << target - score << " apples left to win, good job!";
}
void gameplay()
{
	cout << "Welcome to \"SNAKE\" game!" << endl << "RULES:\n1.Don't crash into walls\n2.You can't bite your tail\n3.You win when you eat enough apples\nPress enter to countinue......" << endl;
	getchar();
	system("cls");
	int height, width;
	cout << "Enter the height and width of the playing field (each value is no less than 10 and no more than 30)" << endl;
	for (; true ;)
	{
		cin >> height >> width;
		if (height >= 10 && height <= 30 && width >= 10 && width <=30)
			break;
		cout << "Invalid input, try again!" << endl;
	}
	system("cls");
	int len_to_win;
	cout << "Enter the length to which you want to grow the snake (from 6 to " << height * width - 5 << ")" << endl;
	for (; true;)
	{
		cin >> len_to_win;
		if (len_to_win >= 6 && len_to_win <= height*width - 5)
			break;
		cout << "Invalid input, try again!" << endl;
	}
	system("cls");
	cout << "To start the game press ENTER";
	getchar();
	getchar();
	game_field field(height, width);
	Apple apple(field);
	Snake snake(field, &apple);
	field.draw();
	hide_cursor();
	int status = -1;
	while (!is_game_over(snake, len_to_win))
	{
		field.draw();
		snake.draw();
		draw_score(snake.Get_length(), len_to_win, field);
		apple.draw(snake.Get_Pos());
		snake.move();
		Sleep(75);
		if (snake.Get_length() == len_to_win)
			status = 1;//win
		if (snake.bit_the_tail())
			status = 2;//uroboros
		if (snake.out_of_field())
			status = 3;//crash
	}
	system("cls");
	if (status == 1)
	{
		set_color("blue");
		cout << "Congratulations, you WON!!!!" << endl;
	}
	if (status == 2)
	{
		set_color("red");
		cout << "We're sorry, you called OUROBOROS. He bit his tail - start again..." << endl;
	}
	if (status == 3)
	{
		set_color("red");
		cout << "It looks like you lost control - start again..." << endl;
	}
	system("pause");
}
