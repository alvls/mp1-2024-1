#include <iostream>
#include <conio.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <windows.h> 
#include <algorithm>
using namespace std;

class Snake {
	int M; int N;
	int condition_game_over; // насколько большой должна быть змейка, чтобы игра закончилась
	int length_snake = 5;
	vector <pair <int, int>> snake_position;
	pair <int, int> apple_position;
	vector <pair <int, int>> available_values_for_random;
	int direction_of_movement; //направление движения змейки 37 - влево, 38 - вверх, 39 - вправо, 224 - вниз
public:
	Snake(int cond_, int M_ = 15, int  N_ = 15) {
		condition_game_over = cond_; M = M_; N = N_;
		if (M < 6) {
			M = 6;
		}
		if (N < 2) {
			N = 2;
		}
		if (condition_game_over < length_snake) {
			condition_game_over = length_snake + 1;
		}
		if (condition_game_over > M * N) {
			condition_game_over = M * N - 1;
		}
		for (int i = 0; i < M; i++) { //создание вектора допустимых значений
			for (int j = 0; j < N; j++) {
				pair <int, int> p;
				p.first = i + 1; p.second = j + 1;
				available_values_for_random.push_back(p);
			}
		}
		for (int i = 0; i < 5; i++) { //внесение начальной позиции змейки
			pair<int, char> p;
			p.first = M - i; p.second = 2;
			snake_position.push_back(p);
			available_values_for_random.erase(available_values_for_random.begin() + M + M - i); // некоторые значения становятся не доступны
		}
		//apple_position.first = 2; apple_position.second = N - 5;
		srand(time(0));
		int i = rand() % available_values_for_random.size();
		apple_position = available_values_for_random[i]; 
		available_values_for_random.erase(available_values_for_random.begin() + i);
		direction_of_movement = 75;
	}
	void rechange() {} //показано, что можно изменять настройки
	void start() {
		bool сhecking_the_victory = true;
		while (length_snake < condition_game_over) {
			// отображение яблока и змейки в консоли 
			HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			pair<int, int> snake_head = snake_position.back();
			for (int j = 0; j < N + 2; j++) {
				for (int i = 0; i < M + 2; i++) {
					if (apple_position.first == i && apple_position.second == j) { // вывод яблока
						SetConsoleTextAttribute(console_color, 12);
						cout << "[ ]";
						continue;
					}
					if (snake_head.first == i && snake_head.second == j) {// вывод головы змейки
						SetConsoleTextAttribute(console_color, 11);
						cout << "[ ]";
						continue;
					}
					if (i == 0 || i == M + 1 || j == 0 || j == N + 1) { // вывод стенок
						SetConsoleTextAttribute(console_color, 15);
						cout << "[ ]";
						continue;
					}
					bool flag = true;
					for (int k = 0; k < length_snake; k++) { // вывод тела змейки
						if (snake_position[k].first == i && snake_position[k].second == j) {
							flag = false;
							SetConsoleTextAttribute(console_color, 10);
							cout << "[ ]";
							break;
						}
					}
					if (flag == false) {
						continue;
					}
					SetConsoleTextAttribute(console_color, 0); // пустое пространство 
					cout << "[ ]";
				}
				cout << "\n";
			}
			Sleep(500); // задержка, 1000 = 1 сек
			// приём символов
			while (_kbhit()) {
				int s = _getch();
				int key = _getch();
				if ((key == 75 && direction_of_movement != 77) || (key == 72 && direction_of_movement != 80) || (key == 77 && direction_of_movement != 75) || (key == 80 && direction_of_movement != 72)) {
					direction_of_movement = key;
				}
			}
			// проверка яблока, его перемещение 
			//перемещение змейки и увеличение змейки
			pair<int, int> p;
			if (direction_of_movement == 75) {
				p.first = snake_position.back().first - 1;
				p.second = snake_position.back().second;
				snake_position.push_back(p);
			}
			else if (direction_of_movement == 72) {
				p.first = snake_position.back().first;
				p.second = snake_position.back().second - 1;
				snake_position.push_back(p);
			}
			else if (direction_of_movement == 77) {
				p.first = snake_position.back().first + 1;
				p.second = snake_position.back().second;
				snake_position.push_back(p);
			}
			else if (direction_of_movement == 80) {
				p.first = snake_position.back().first;
				p.second = snake_position.back().second + 1;
				snake_position.push_back(p);
			}
			//удаление из векторов допустимых для яблока значений после перемещения змейки
			for (int i = 0; i < available_values_for_random.size(); i++) {
				for (int j = 0; j < snake_position.size(); j++) {
					if (snake_position[j] == available_values_for_random[i]) {
						available_values_for_random.erase(available_values_for_random.begin() + i);
					}
				}			
			}
			// проверка яблока, его перемещение или удаление хвоста змейки
			if (apple_position == snake_position.back()) {
				srand(time(0));
				int i = rand() % available_values_for_random.size();
				apple_position = available_values_for_random[i];
				available_values_for_random.erase(available_values_for_random.begin() + i);
				length_snake++;
			}
			else {
				available_values_for_random.push_back(snake_position.front());
				snake_position.erase(snake_position.begin());
			}
			//проверка проигрыша
			for (int j = 0; j < snake_position.size(); j++) {
				for (int i = 0; i != j; i++) {
					if (snake_position[i] == snake_position[j]) {
						system("cls"); // очистка консоли
						cout << "GAME OVER";
						сhecking_the_victory = false;
						break;
					}
				}
				if (p.first == 0 || p.first == M + 1 || p.second == 0 || p.second == N + 1) {
					system("cls"); // очистка консоли
					cout << "GAME OVER";
					сhecking_the_victory = false;
					break;
				}
			}
			if (сhecking_the_victory == false) {
				break;
			}
			system("cls"); // очистка консоли
		}
		if (сhecking_the_victory == true) {
			cout << "YOU WON";
		}
		system("pause");
	}

};


void main() {
	//int l = _getch();
	//cout << l;
	Snake A{ 10 };
	A.start();
}