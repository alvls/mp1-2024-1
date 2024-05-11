#include <iostream>
#include "Snake.h"

using namespace std;

int main() {
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (true) {
		SnakeGame sg(15, 20, 7, 300);
		sg.Play();
	}
	system("pause");
	return 0;
}