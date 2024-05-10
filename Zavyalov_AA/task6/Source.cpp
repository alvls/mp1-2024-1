#include <iostream>
#include "Snake.h"

using namespace std;

int main() {
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "Hello world!";
	SetConsoleTextAttribute(hConsole, 13);
	std::cout << "Hello world!";
	SetConsoleTextAttribute(hConsole, 15);

	/*for (int i = 3; i < 6; i++) {
		for (int j = 3; j < 6; j++) {
			COORD cord = { i, j };
			Food f = Food(cord);
			f.Show();
			Sleep(1000);
			f.Hide();
		}
	}*/

	//for (int i = 0; i < 254; i++) {
	//	cout << i << ' ' << char(i) << endl;
	//}

	Field f(5, 9);
	f.Show();
	Sleep(1000);
	Food fo({ 7, 4 });
	fo.Show();
	Sleep(1000);
	f.Hide();
	system("pause");

	return 0;
}