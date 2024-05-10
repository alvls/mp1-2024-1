#include <iostream>
#include "Snake.h"

using namespace std;

int main() {
	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, 15);
	//for (int i = 0; i < 254; i++) {
	//	cout << i << ' ' << char(i) << endl;
	//}
	/*endAnimation(15, 20, 'l');
	Snake s({ 5, 8 });
	s.Show();
	Sleep(500);
	s.Move('l');
	Sleep(500);
	s.Move('u');
	Sleep(500);
	s.Move('r');
	Sleep(500);
	s.Move('d');
	Sleep(500);
	s.Eat({ s.getHead().X, short(s.getHead().Y - 1) });
	Sleep(500);
	Field f(15, 20);
	f.Show();
	Sleep(1000);
	Food fo({ 7, 4 });
	fo.Show();
	Sleep(1000);
	f.Hide();*/
	SnakeGame sg(15, 20, 6);
	sg.Play();
	WORD s;
	int t;
	while (true) {
		wait_for_key(500, s, t);
		if (s != 37)
			cout << "gsd " << t << endl;
	}
	system("pause");


	return 0;
}