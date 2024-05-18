#include "Header.h"

void main() {
	std::cout << "Enter the difficulty(game speed): \n";
	std::cout << "1 - very easy, 2 - easy, 3 - normal \n";
	std::cout << "4 - hard, 5 - insane, 6 - ???\n";
	ui dif = 0;
	do {
		std::cin >> dif;
	} while ((dif > 6) || (dif < 1));


	//enter width, height, snake len
	// coord = {0, 0}
try {
	// w h sl; 2 2 dif
	Game g(5, 3, 2);
	g.play(2, 2, 2);
	system("pause");
}
catch (char* q) {
	std::cout << "Sorry, but " << q << std::endl;
	system("pause");
}
}