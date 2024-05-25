#include "Snake.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

bool wait_for_key(int timeout_milliseconds, WORD& ch, int& timeleft) {
	HANDLE tui_handle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD tui_evtc = 0;
	DWORD curtime = GetTickCount();
	DWORD deadline = curtime + timeout_milliseconds;
	INPUT_RECORD tui_inrec = { 0 };
	DWORD tui_numread = 0;

	FlushConsoleInputBuffer(tui_handle);

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
				std::cout << " You won! Press any key to continue. ";
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
		std::cout << " You lost. Press any key to continue. ";
		_getch();
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

void Snake::Show() {
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

void Snake::Hide() {
	SetConsoleCursorPosition(hConsole, head);
	std::cout << char(32);
	for (COORD x : body) {
		SetConsoleCursorPosition(hConsole, x);
		std::cout << char(32);
	}
}

bool Snake::Move(WORD direction) {
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
		head = { head.X, short(head.Y - 1) };
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

void Snake::Eat(COORD foodpos) {
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

COORD Snake::getHead() { return head; }

std::vector<COORD> Snake::getBody() { return body; }

int Snake::getSize() { return size; }

void Field::Show() {
	SetConsoleTextAttribute(hConsole, 15); // 15 = white
	for (short i = 0; i < width + 2; i++) {
		COORD pos = { i, 0 };
		SetConsoleCursorPosition(hConsole, pos);
		std::cout << char(219);
		pos = { i, short(height + 1) };
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

void Field::Hide() {
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

void Food::Show(int color = 6) {
	SetConsoleCursorPosition(hConsole, position);
	SetConsoleTextAttribute(hConsole, color);
	std::cout << char(219);
}

void Food::Hide() {
	SetConsoleCursorPosition(hConsole, position);
	std::cout << char(32);
}

void SnakeGame::SetGoal() {
	SetConsoleTextAttribute(hConsole, 15);

	SetConsoleCursorPosition(hConsole, { 0, 0 });
	for (int i = 0; i < width + 40; i++) std::cout << " ";

	SetConsoleCursorPosition(hConsole, { 0, 0 });
	std::cout << "Set the goal that is more than 4: ";
	std::cin >> goal;
	while (goal < 5) {
		std::cout << "Set the goal that is more than 4: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> goal;
	}

	SetConsoleCursorPosition(hConsole, { 0, 0 });
	for (int i = 0; i < width + 30; i++) {
		for (int j = 0; j < height + 10; j++) 
			std::cout << " ";
		std::cout << std::endl;
	}

}

void SnakeGame::Play() {
	SetGoal();

	std::srand(std::time(NULL));
	short headx = 2 + rand() % (width - 6), heady = 2 + rand() % (height - 2);
	snake = Snake({ headx, heady });

	field.Show();
	snake.Show();
	SetConsoleTextAttribute(hConsole, 15);
	SetConsoleCursorPosition(hConsole, { short(width + 3), 0 });
	std::cout << "Current score: " << snake.getSize();
	SetConsoleCursorPosition(hConsole, { short(width + 20), 0 });
	std::cout << "Your goal: " << goal;

	WORD KB_code = KB_LEFT, prev_KB_code = KB_LEFT;
	bool isFoodEaten = true;
	bool win = true;
	COORD foodpos = { 0,0 };
	while (true) {
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
		wait_for_key(speed, KB_code, timeleft);

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
		default:
			KB_code = prev_KB_code;
			break;
		}

		switch (KB_code)
		{
		case KB_LEFT:
			if (snake.getHead().X - 1 < 1 || isBody({ short(snake.getHead().X - 1), snake.getHead().Y }, snake.getBody())) {
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
			if (snake.getHead().Y - 1 < 1 || isBody({ snake.getHead().X , short(snake.getHead().Y - 1) }, snake.getBody())) {
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

		SetConsoleTextAttribute(hConsole, 15);
		SetConsoleCursorPosition(hConsole, { short(width + 3), 0 });
		std::cout << "Current score: " << snake.getSize();

		if (win == false) break;
		if (snake.getSize() == goal) break;

		if (!isFoodEaten) snake.Move(KB_code);
		SetConsoleCursorPosition(hConsole, { short(width + 3), short(height + 3) });
		prev_KB_code = KB_code;

		while (GetTickCount() < curtime + timeleft) {}
	}
	if (win) {
		snake.Hide();
		field.Hide();
		SetConsoleCursorPosition(hConsole, foodpos);
		std::cout << char(32);
		end_animation(height, width, 'w');

		SetConsoleCursorPosition(hConsole, { short(height + 4), width });
		for (int i = 0; i < 37; i++) {
			std::cout << char(32);
		}
	}
	else
	{
		snake.Hide();
		field.Hide();
		SetConsoleCursorPosition(hConsole, foodpos);
		std::cout << char(32);
		end_animation(height, width, 'l');

		SetConsoleCursorPosition(hConsole, { short(height + 4), width });
		for (int i = 0; i < 37; i++) {
			std::cout << char(32);
		}
	}
}