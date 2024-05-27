#include "Header.h"


void main() {
	std::cout << "Enter the difficulty(game speed): \n";
	std::cout << "1 - very easy, 2 - easy, 3 - normal \n";
	std::cout << "4 - hard, 5 - insane, 6 - ???\n";
	ui dif = 0;
	do {
		scanf_s("%u", &dif);
		//std::cin >> dif;
		std::cin.ignore(INT_MAX, '\n');

	} while ((dif > 6) || (dif < 1));

	std::cout << "Enter the field width: \n";
	ui width = 0;
	scanf_s("%u", &width);
	std::cin.ignore(INT_MAX, '\n');
	while ((width < 5) || (width > 1000)) {
		if (width < 5)
			std::cout << "Too small field. Please, enter again\n";
		else
			std::cout << "Too big field. Please, enter again\n";
		scanf_s("%u", &width);
		std::cin.ignore(INT_MAX, '\n');
	}

	std::cout << "Enter the field height: \n";
	ui height = 0;
	scanf_s("%u", &height);
	std::cin.ignore(INT_MAX, '\n');
	while ((height < 3) || (height > 1000)) {
		if (height < 3)
			std::cout << "Too small field. Please, enter again\n";
		else
			std::cout << "Too big field. Please, enter again\n";
		scanf_s("%u", &height);
		std::cin.ignore(INT_MAX, '\n');
	}

	std::cout << "Enter the snake start len: \n";
	ui snake_len = 0;
	scanf_s("%u", &snake_len);
	std::cin.ignore(INT_MAX, '\n');
	while ((snake_len < 1) || (width - snake_len < 3)) {
		if (snake_len < 1)
			std::cout << "It's not a SNAKE. Please, enter again\n";
		if (width - snake_len < 3)
			std::cout << "Your snake has broken the fourth wall. \nPlease, try to save the reality and make it a little shorter\n";
		scanf_s("%u", &snake_len);
		std::cin.ignore(INT_MAX, '\n');
	}

	std::cout << "Enter the goal (win snake len): \n";
	ui win_snake_len = 0;
	scanf_s("%u", &win_snake_len);
	std::cin.ignore(INT_MAX, '\n');
	while ((win_snake_len < snake_len) || (win_snake_len >= height*width )) {
		if (win_snake_len < snake_len)
			std::cout << "It's not an interesting game. Please, enter again\n";
		if (win_snake_len >= height * width)
			std::cout << "It's ... very hard. Idk, try again maybe?..";
		scanf_s("%u", &snake_len);
		std::cin.ignore(INT_MAX, '\n');
	}

	ui zero_x = 2, zero_y = 2;
try {
	HANDLE Con = GetConsoleHandle();
	COORD pos = { 0,0 };
	SetConsoleCursorPosition(Con, pos);
	system("cls");

	Game g(width, height, snake_len, win_snake_len);
	g.play(zero_x, zero_y, dif);
	system("pause");
}
catch (char* q) {
	std::cout << "Sorry, but " << q << std::endl;
	system("pause");
}
}