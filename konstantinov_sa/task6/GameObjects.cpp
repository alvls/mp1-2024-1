#include "GameObjects.h"
//#include "Game.h"
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

			if (target && dynamic_pointer_cast<Food>(target)) { 
				growstate = 1;
				tail->willgrow = 1; //хвост вырастет, на следующем апдейте голова найдёт новый сегмент
			}

			game->move(x, y, tx, ty);
		}
	}
	
	
}

void Snake::update(){
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
	if (growstate) { //хвост вырос на прошлом апдейте
		tail = tail->next;
		growstate = 0;
	}
	next->transmit(x, y);
	crawl(nx, ny);
}

void Segment::transmit(int nx, int ny)
{
	tx = nx;
	ty = ny;
	if (next)
		next->transmit(x, y);
	else {
		
	}
}

void Segment::update()
{
	if (willgrow && !next) {
		int ox = x;
		int oy = y;
		game->move(x, y, tx, ty);
		
		next = game->create<Segment>(ox, oy);
		next->init(id + 1);
		willgrow = 0;
		
		
	}
	else {
		game->move(x, y, tx, ty);
	}
	
	
	

}
