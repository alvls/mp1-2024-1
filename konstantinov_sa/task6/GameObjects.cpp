#include "GameObjects.h"
#include "Game.h"
#include<iostream>
#include<memory>

void Snake::crawl(int tx,int ty) {
	cout << "CRAWL TO " << tx << " " << ty << endl;
	
	if (((tx != x) || (ty != y)) && (game->isInBounds(tx, ty))) {
		cout << "NEW LOC "<<endl;
		shared_ptr<Gobject> target = game->get(tx, ty);
		cout << target << endl;
		if ((!target) || (!dynamic_pointer_cast<Wall>(target))) {
			cout << "NO WALL\n";
			game->move(x, y, tx, ty);
		}
	}
	
	
}

void Snake::update() {
	std::cout << "SNAKE " << x << ' ' << y << '\n';
	Dir key = game->key;
	int nx = x;
	int ny = y;
	switch (key) {
	case Dir::R:
		nx += 1;
		break;
	case Dir::D:
		ny += 1;
		break;
	case Dir::L:
		nx -= 1;
		break;
	case Dir::U:
		ny -= 1;
		break;
	}
	crawl(nx, ny);
}
