#include <iostream>
#include <ctime>
#include <locale.h>
#include <vector>
#include <conio.h>
#include <Windows.h>
using namespace std;

struct Point {
	int x, y;
};

class Snake {
public:
	std::vector<Point> body;
	char direction = 'l';

	Snake(int init_x, int init_y) {
		if (init_x < 7) init_x = 7;

		for (int i = 4; i >= 0; i--) {
			body.push_back({ init_x - i, init_y });
		}
	}

	void move() {
		Point newHead = body.front();
		switch (direction) {
		case 'u': newHead.y--; break;
		case 'd': newHead.y++; break;
		case 'l': newHead.x--; break;
		case 'r': newHead.x++; break;
		}
		body.insert(body.begin(), newHead);
		body.pop_back();
	}

	void grow() {
		body.push_back(body.back());
	}

	bool checkCollision(const int width, const int height) {
		Point head = body.front();

		if (head.x < 1 || head.x >= width - 1 || head.y < 1 || head.y >= height - 1) {
			return true;
		}

		for (int i = 1; i < body.size(); i++) {
			if (body[i].x == head.x && body[i].y == head.y) return true;
		}
		return false;
	}
};

class Game {
	Snake snake;
	Point food;
	int width, height;
	bool gameOver;
	int speed;
	int fruitsEaten = 0;
	int targetSize;

public:
	Game(int w, int h, int s, int tSize) : snake(w / 2, h / 2), width(w), height(h), gameOver(false), speed(s), targetSize(tSize) {
		placeFood();
	}

	void placeFood() {
		while (true) {
			food = { rand() % (width - 2) + 1, rand() % (height - 2) + 1 };
			bool collision = false;
			for (const auto& p : snake.body) {
				if (p.x == food.x && p.y == food.y) {
					collision = true;
					break;
				}
			}
			if (!collision) break;
		}
	}

	void input() {
		if (_kbhit()) {
			switch (_getch()) {
			case 'w': if (snake.direction != 'd') snake.direction = 'u'; break;
			case 's': if (snake.direction != 'u') snake.direction = 'd'; break;
			case 'a': if (snake.direction != 'r') snake.direction = 'l'; break;
			case 'd': if (snake.direction != 'l') snake.direction = 'r'; break;
			}
		}
	}

	void logic() {
		snake.move();
		if (snake.body.front().x == food.x && snake.body.front().y == food.y) {
			snake.grow();
			placeFood();
			fruitsEaten++;
		}
		if (snake.checkCollision(width, height)) {
			gameOver = true;
		}
	}

	void run() {
		while (!gameOver) {
			input();
			logic();
			display();
			if (snake.body.size() >= targetSize) {
				gameOver = true;
				cout << "Вы достигли желаемого размера змейки. ПОЗДРАВЛЯЕМ С ПОБЕДОЙ! " << endl;
				return;
			}
			Sleep(speed);
		}
		if (fruitsEaten == (width * height) - 5) {
			cout << "Вы собрали максимальное количество фруктов, ПОЗДРАВЛЯЕМ С ПОБЕДОЙ! " << endl;
		}
		else {
			cout << "Игра окончена!" << endl;
		}
	}

private:
	void display() {
		system("cls");
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				bool isBodyPart = false;
				for (int i = 0; i < snake.body.size(); i++) {
					if (snake.body[i].x == x && snake.body[i].y == y) {
						if (i == 0) { 
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Цвет головы
							cout << "O";
						}
						else {
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY); // Цвет тела
							cout << "*";
						}
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Сброс цвета
						isBodyPart = true;
						break;
					}
				}
				if (!isBodyPart) {
					if (x == food.x && y == food.y) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Цвет фрукта
						cout << "F";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Сброс цвета
					}
					else if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
						cout << "#";
					}
					else {
						cout << " ";
					}
				}
			}
			cout << endl;
		}
		cout << "Количество съеденных фруктов: " << fruitsEaten << endl;
		cout << "Текущая длина змейки: " << fruitsEaten + 5 << endl;
	}
};

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(nullptr));

	char playAgain = 'y';
	std::cout << "Добро пожаловать в игру Змейка!" << std::endl;
	std::cout << "Управление: 'w' - вверх, 's' - вниз, 'a' - влево, 'd' - вправо.\n" << std::endl;

	while (playAgain == 'y') {
		int width, height, speed, targetSize;
		do {
			std::cout << "Введите ширину игрового поля (рекомендуется 30): ";
			std::cin >> width;
			if (width <= 6) {
				std::cout << "Ширина должна быть не менее 7. Попробуйте снова.\n";
			}
		} while (width <= 6);

		do {
			std::cout << "Введите высоту игрового поля (рекомендуется 20): ";
			std::cin >> height;
			if (height <= 6) {
				std::cout << "Высота должна быть не менее 7. Попробуйте снова.\n";
			}
		} while (height <= 6);

		do {
			std::cout << "Введите скорость змейки (рекомендуется 100, чем ниже число, тем быстрее змейка): ";
			std::cin >> speed;
			if (speed <= 0) {
				std::cout << "Скорость должна быть положительным числом. Попробуйте снова.\n";
			}
		} while (speed <= 0);

		int maxPossibleSize = width * height;
		do {
			std::cout << "До какого размера хотите вырастить змейку (от 6 до " << maxPossibleSize << "): ";
			std::cin >> targetSize;
			if (targetSize < 6 || targetSize > maxPossibleSize) {
				std::cout << "Невозможный размер змейки. Попробуйте снова.\n";
			}
		} while (targetSize < 6 || targetSize > maxPossibleSize);

		Game game(width + 2, height + 2, speed, targetSize);
		game.run();

		std::cout << "\nХотите сыграть еще раз? (введите 'y' если да / введите 'n' если нет): ";
		std::cin >> playAgain;
		while (playAgain != 'y' && playAgain != 'n') {
			std::cin >> playAgain;
		}
	}
	std::cout << "Спасибо за игру!" << std::endl;

	std::cin.get();
	return 0;
}
