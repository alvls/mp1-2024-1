#include <iostream>
#include "Snake.h"

using namespace std;

int main() {
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SnakeGame sg(15, 20, 6);
	sg.Play();
	system("pause");
	return 0;
}