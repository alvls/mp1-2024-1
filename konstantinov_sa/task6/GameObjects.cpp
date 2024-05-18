#include "GameObjects.h"
#include "Game.h"
#include<iostream>

void Snake::update() {
	std::cout << "SNAKE " << x << ' ' << y << '\n';
	Dir key = game->key;
	switch (key) {
	case Dir::R:
		game->move(x, y, x + 1, y);
		
		break;
	}
}
