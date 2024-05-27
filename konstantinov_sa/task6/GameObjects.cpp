#include "GameObjects.h"
#include "Game.h"
#include<iostream>
#include<memory>
using namespace std;

void Snake::crawl(int tx, int ty) {
#ifdef DEBUG_PRINT
	cout << "CRAWL TO " << tx << " " << ty << endl;
#endif

	if (((tx != x) || (ty != y)) && (game->isInBounds(tx, ty))) {
#ifdef DEBUG_PRINT
		cout << "NEW LOC " << endl;
#endif
		shared_ptr<Gobject> target = game->get(tx, ty);
#ifdef DEBUG_PRINT
		cout << target << endl;
#endif
		if ((!target) || ((!dynamic_pointer_cast<Wall>(target)) && (!dynamic_pointer_cast<Segment>(target)))) {
#ifdef DEBUG_PRINT
			cout << "NO WALL\n";
#endif

			if (target && dynamic_pointer_cast<Food>(target)) {
				
				growstate = 1;
				tail->willgrow = 1; //хвост вырастет, на следующем апдейте голова найдёт новый сегмент
			}

			game->move(x, y, tx, ty);
		}
		else {
			game->move(x, y, tx, ty);
			symbol = 'X';
			game->over();
		}
	}
}

void Snake::update() {
#ifdef DEBUG_PRINT
	std::cout << "SNAKE " << x << ' ' << y << '\n';
#endif
	Controls key = game->key;
	//cout << "\t\tKEY " << (int)key << endl;
	int nx = 0;
	int ny = 0;
	switch (key) {
	case Controls::R:
		nx += 1;
		break;
	case Controls::D:
		ny += 1;
		break;
	case Controls::L:
		nx -= 1;
		break;
	case Controls::U:
		ny -= 1;
		break;
	default:
		break;
	}
	if (nx || ny) {
		if ((nx != -dx) && (ny != -dy)) {

			dx = nx; dy = ny;
		}
	}
	if (growstate) { //хвост вырос на прошлом апдейте
		tail = tail->next;
		growstate = 0;
		if (game->snakelen == game->targetlen)
			game->over();
	}
	//cout << "\t\tdx dy " << dx << " " << dy<<endl;
	next->transmit(x, y);
	crawl(x + dx, y + dy);
}

void Segment::init(int id_, shared_ptr<Segment> next_) {
	id = id_;
	if (id % 3 == 1)
		color = FOREGROUND_GREEN | FOREGROUND_BLUE;
	else if (id % 3 == 2)
		color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	next = next_;
#ifdef DEBUG_PRINT
	cout << "seg init id " << id << endl;
#endif
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
#ifdef DEBUG_PRINT
	cout << "SEGMENT " << id << " to: " << tx << " " << ty << endl;
#endif
	if (willgrow && !next) {
#ifdef DEBUG_PRINT
		cout << "NEW SEGMENT" << endl;
#endif
		int ox = x;
		int oy = y;

		game->move(x, y, tx, ty);

		next = game->create<Segment>(ox, oy);
		next->init(id + 1);
		willgrow = 0;


	}
	else {
		if (x != tx || y != ty)
			game->move(x, y, tx, ty);
	}
}
