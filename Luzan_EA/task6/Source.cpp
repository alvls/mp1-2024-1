#include "Header.h"

void main() {
	//EmptyField f(4, 3);
	//f.drawField(1, 1);
	Game g(8, 20, 5, 'O', 'o');
	g.play(5, 5);
	system("pause");
}