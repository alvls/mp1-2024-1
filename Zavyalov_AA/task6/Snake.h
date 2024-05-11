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

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

bool wait_for_key(int timeout_milliseconds, WORD& ch, int& timeleft) {
	HANDLE tui_handle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD tui_evtc = 0;
	DWORD curtime = GetTickCount();
	DWORD deadline = curtime + timeout_milliseconds;
	INPUT_RECORD tui_inrec = { 0 };
	DWORD tui_numread = 0;

	while (GetTickCount() < deadline) {
		if (tui_evtc > 0) {
			ReadConsoleInput(tui_handle, &tui_inrec, 1, &tui_numread);
			if (tui_inrec.EventType == KEY_EVENT) {
				if (tui_inrec.Event.KeyEvent.bKeyDown) {
					ch = tui_inrec.Event.KeyEvent.wVirtualKeyCode;
					timeleft = deadline - GetTickCount();
					return true;
				}
			}
		}
		YieldProcessor();
		GetNumberOfConsoleInputEvents(tui_handle, &tui_evtc);
	}
	timeleft = 0;
	return false;
}
void end_animation(short n, short m, char c) {
	if (c == 'w') {
		while (true) {
			for (int i = 1; i < 15; i++) {
				SetConsoleCursorPosition(hConsole, { short(n + 4), m });
				SetConsoleTextAttribute(hConsole, i);
				std::cout << "You won! Press any key to continue. ";
				WORD c;
				int placeholder;
				bool x = wait_for_key(150, c, placeholder);
				if (x) return;
			}

		}
	}
	else if (c == 'l')
	{
		SetConsoleCursorPosition(hConsole, { short(n + 4), m });
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << "You lost. ";
	}
}
bool is_restricted(COORD pos, std::vector<COORD> restricted_positions) {
	for (COORD coord : restricted_positions) {
		if (pos.X == coord.X && pos.Y == coord.Y) {
			return true;
		}
	}
	return false;
}

bool isBody(COORD nextheadpos, std::vector<COORD> body_positions) {
	for (COORD element : body_positions) {
		if (nextheadpos.X == element.X && nextheadpos.Y == element.Y) {
			return true;
		}
	}
	return false;
}
class Snake
{
	COORD head;
	std::vector<COORD> body;
	int size = 5;
public:
	Snake() {};
	Snake(COORD headpos) : head(headpos) {}
	void Show() {
		SetConsoleTextAttribute(hConsole, 4);
		SetConsoleCursorPosition(hConsole, head);
		std::cout << char(219);
		SetConsoleTextAttribute(hConsole, 2);
		for (short i = 1; i <= 4; i++) {
			SetConsoleTextAttribute(hConsole, 2);
			COORD pos = { head.X + i, head.Y };
			SetConsoleCursorPosition(hConsole, pos);
			std::cout << char(219);
			body.push_back(pos);
		}
	}
	void Hide() {
		SetConsoleCursorPosition(hConsole, head);
		std::cout << char(32);
		for (COORD x : body) {
			SetConsoleCursorPosition(hConsole, x);
			std::cout << char(32);
		}
	}
	bool Move(WORD direction) {
		if (direction == KB_LEFT) {
			for (auto element : body) {
				if ((element.X == head.X - 1) && (element.Y == head.Y)) {
					return false;
				}
			}
			std::vector<COORD> new_body(size - 1);
			new_body[0] = head;
			head = { short(head.X - 1), head.Y };
			for (int i = 1; i < size - 1; i++) {
				new_body[i] = body[i - 1];
			}
			SetConsoleCursorPosition(hConsole, body[size - 2]);
			std::cout << char(32);
			SetConsoleTextAttribute(hConsole, 2);
			SetConsoleCursorPosition(hConsole, new_body[0]);
			std::cout << char(219);
			SetConsoleTextAttribute(hConsole, 4);
			SetConsoleCursorPosition(hConsole, head);
			std::cout << char(219);
			body = new_body;
			return true;
		}
		if (direction == KB_RIGHT) {
			for (auto element : body) {
				if ((element.X == head.X + 1) && (element.Y == head.Y)) {
					return false;
				}
			}
			std::vector<COORD> new_body(size - 1);
			new_body[0] = head;
			head = { short(head.X + 1), head.Y };
			for (int i = 1; i < size - 1; i++) {
				new_body[i] = body[i - 1];
			}
			SetConsoleCursorPosition(hConsole, body[size - 2]);
			std::cout << char(32);
			SetConsoleTextAttribute(hConsole, 2);
			SetConsoleCursorPosition(hConsole, new_body[0]);
			std::cout << char(219);
			SetConsoleTextAttribute(hConsole, 4);
			SetConsoleCursorPosition(hConsole, head);
			std::cout << char(219);
			body = new_body;
			return true;
		}
		if (direction == KB_UP) {
			for (auto element : body) {
				if ((element.X == head.X) && (element.Y == head.Y - 1)) {
					return false;
				}
			}
			std::vector<COORD> new_body(size - 1);
			new_body[0] = head;
			head = { head.X, short(head.Y - 1)};
			for (int i = 1; i < size - 1; i++) {
				new_body[i] = body[i - 1];
			}
			SetConsoleCursorPosition(hConsole, body[size - 2]);
			std::cout << char(32);
			SetConsoleTextAttribute(hConsole, 2);
			SetConsoleCursorPosition(hConsole, new_body[0]);
			std::cout << char(219);
			SetConsoleTextAttribute(hConsole, 4);
			SetConsoleCursorPosition(hConsole, head);
			std::cout << char(219);
			body = new_body;
			return true;
		}
		if (direction == KB_DOWN) {
			for (auto element : body) {
				if ((element.X == head.X) && (element.Y == head.Y + 1)) {
					return false;
				}
			}
			std::vector<COORD> new_body(size - 1);
			new_body[0] = head;
			head = { head.X, short(head.Y + 1) };
			for (int i = 1; i < size - 1; i++) {
				new_body[i] = body[i - 1];
			}
			SetConsoleCursorPosition(hConsole, body[size - 2]);
			std::cout << char(32);
			SetConsoleTextAttribute(hConsole, 2);
			SetConsoleCursorPosition(hConsole, new_body[0]);
			std::cout << char(219);
			SetConsoleTextAttribute(hConsole, 4);
			SetConsoleCursorPosition(hConsole, head);
			std::cout << char(219);
			body = new_body;
			
			return true;
		}
	}
	void Eat(COORD foodpos) {
		std::vector<COORD> new_body(size);
		new_body[0] = head;
		head = foodpos;
		for (int i = 1; i < size; i++) {
			new_body[i] = body[i - 1];
		}
		body = new_body;
		SetConsoleTextAttribute(hConsole, 2);
		SetConsoleCursorPosition(hConsole, body[0]);
		std::cout << char(219);
		SetConsoleTextAttribute(hConsole, 4);
		SetConsoleCursorPosition(hConsole, head);
		std::cout << char(219);
		size++;
	}
	COORD getHead() { // для class game, для проверки на то можно ли ехать куда-то (не стена ли там)
		return head;
	}
	std::vector<COORD> getBody() { // для проверки на то, можно ли создать еду в клетке
		return body;
	}
	int getSize() { return size; }
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
	void Show(int color = 6) {
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
	Snake snake;
	Field field;
	short width;
	short height;
	int speed; // period between tacts in milliseconds
	int goal;
public:
	SnakeGame(short n, short m, int goal_, int speed_ = 500): field(n, m), width(m), height(n), goal(goal_), speed(speed_){}
	void Play() {
		std::srand(std::time(NULL));
		short headx = 2 + rand() % (width - 6), heady = 2 + rand() % (height - 2);
		snake = Snake({ headx, heady });
		field.Show();
		snake.Show();
		WORD KB_code = KB_LEFT, prev_KB_code = KB_LEFT;
		bool isFoodEaten = true;
		bool win = true;
		COORD foodpos = { 0,0 };
		while (true) {
			
			/*std::vector<COORD> restricted = snake.getBody();
			restricted.push_back(snake.getHead());
			COORD foodpos = restricted[0];
			while (is_restricted(foodpos, restricted)) {
				short foodx = 1 + rand() % width, foody = 1 + rand() % height;
				foodpos = { foodx, foody };
			}
			Food food(foodpos);*/
			DWORD curtime = GetTickCount();
			if (isFoodEaten) {
				std::vector<COORD> restricted = snake.getBody();
				restricted.push_back(snake.getHead());
				foodpos = restricted[0];
				while (is_restricted(foodpos, restricted)) {
					short foodx = 1 + rand() % width, foody = 1 + rand() % height;
					foodpos = { foodx, foody };
				}
				Food food(foodpos);
				food.Show();
				isFoodEaten = false;
			}
			int timeleft;
			//DWORD curtime = GetTickCount();
			wait_for_key(speed, KB_code, timeleft);
			//DWORD curtime = GetTickCount();

			switch (KB_code)
			{
			case KB_LEFT:
				if (prev_KB_code == KB_RIGHT) {
					KB_code = KB_RIGHT;
				}
				break;

			case KB_RIGHT:
				if (prev_KB_code == KB_LEFT) {
					KB_code = KB_LEFT;
				}              
				break;

			case KB_UP:
				if (prev_KB_code == KB_DOWN) {
					KB_code = KB_DOWN;
				}               
				break;

			case KB_DOWN:
				if (prev_KB_code == KB_UP) {
					KB_code = KB_UP;
				}
				break;

			}

			switch (KB_code)
			{
			case KB_LEFT:
				if (snake.getHead().X - 1 < 1 || isBody({ short(snake.getHead().X - 1), snake.getHead().Y}, snake.getBody())) {
					win = false;
				}
				else
				{
					if (foodpos.X == snake.getHead().X - 1 && foodpos.Y == snake.getHead().Y) {
						snake.Eat(foodpos);
						isFoodEaten = true;
					}
				}
				break;
			case KB_RIGHT:
				if (snake.getHead().X + 1 > width || isBody({ short(snake.getHead().X + 1), snake.getHead().Y }, snake.getBody())) {
					win = false;
				}
				else
				{
					if (foodpos.X == snake.getHead().X + 1 && foodpos.Y == snake.getHead().Y) {
						snake.Eat(foodpos);
						isFoodEaten = true;
					}
				}
				break;
			case KB_UP:
				if (snake.getHead().Y - 1 < 1 || isBody({ snake.getHead().X , short( snake.getHead().Y - 1) }, snake.getBody())) {
					win = false;
				}
				else
				{
					if (foodpos.X == snake.getHead().X && foodpos.Y == snake.getHead().Y - 1) {
						snake.Eat(foodpos);
						isFoodEaten = true;
					}
				}
				break;
			case KB_DOWN:
				if (snake.getHead().Y + 1 > height || isBody({ snake.getHead().X , short(snake.getHead().Y + 1) }, snake.getBody())) {
					win = false;
				}
				else
				{
					if (foodpos.X == snake.getHead().X && foodpos.Y == snake.getHead().Y + 1) {
						snake.Eat(foodpos);
						isFoodEaten = true;
					}
				}
				break;
			default:
				break;
			}

			if (win == false) break;
			if (snake.getSize() == goal) break;
			
			snake.Move(KB_code);
			prev_KB_code = KB_code;

			while (DWORD ds = GetTickCount() < curtime + timeleft) {}
			std::cin.clear();
			// hod igroka
			//Sleep(500);
		}
		if (win) {
			end_animation(height, width, 'w');
		}
		else
		{
			end_animation(height, width, 'l');
		}
	}
	void End() {
		field.Hide();
		snake.Hide();
	}
};