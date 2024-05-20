#include "Game.h"
#include <iostream>
#include "GameObjects.h"
#include <conio.h> //-
#include <windows.h> //-
#include <ctime>
//#include <random>
using namespace std;

Setting Game::settings[SETTINGS_COUNT] = {};

void Game::initSettings()
{
	Setting Game::settings[] = {
		{"maxfood", 1, 1, 100, &maxfood, "max food"},
		{"wallcount", 0, 5, 100, 5, "wc"}
	};
}




template<typename T>
shared_ptr<T> Game::create(int x, int y)
{
	shared_ptr<T> obj = make_shared<T>(this, x, y);
	gmap[y][x] = obj;
	auto activeObj = dynamic_pointer_cast<ActiveGobject>(obj);
	if (activeObj) {
		activeObjects.push_back(activeObj);
	}
	return obj;
}

void Game::buildMap(int sizex, int sizey) //матрица - массив строк
{
	activeObjects.clear();
	sx = sizex + 2; sy = sizey + 2;
	srand(static_cast<unsigned>(time(nullptr)));
	gmap.clear();
	gmap.resize(sy);
	for (auto& l : gmap) {
		l.resize(sx);
	}
	cout << "resize y = "<<gmap.size()<<" x = "<<gmap[0].size()<<endl;

	for (int i = 0;i < 2;i++) {
		for (int j = 0;j < sx;j++) {
			cout << "wall " << i << " " << j << endl;
			create<Wall>(j,i);
			create<Wall>(j, sy - i-1);
		}
		for (int j = 2;j < sy - 2;j++) {
			create<Wall>(i, j);
			create<Wall>(sx -i-1, j);
		}
	}
	cout << "walls\n";
	

	int sx = 11;
	int sy = 4;
	auto s = create<Snake>(sx, sy);
	
	auto seg = create<Segment>(sx-1, sy);
	seg->init(sx-1);
	s->next = seg;
	auto prev = seg;
	for (int i = sx - 2;i > sx - 2-1;i--) {
		seg = create<Segment>(i, sy);
		seg->init(i);
		prev->next = seg;
		
		prev = seg;
	}
	s->tail = seg;
	
	placeRandWalls(50, 50);

	create<Food>(12, 4);
	create<Food>(14, 4);
	create<Food>(12, 7);
	system("cls");
}

void Game::printmap()
{
	//cout << endl;
	for (int i = 0;i < sy;i++) {
		for (int j = 0;j < sx;j++) {
			if (gmap[i][j]) {
				renderObj(gmap[i][j]);
			}
			else {
				cout << ' ';
			}
				
		}
		cout << endl;
	}
	cout << endl;
}

void Game::update() {
	//system("cls");
	cursorToZero();
	//cout << "! UPDATE\n";
	getInput();
	//cout << (int)key << endl;

	for (auto& obj : activeObjects) {
		//cout << " --- ACTIVE UPD\n";
		obj->update();
	}

	if (foodcount < maxfood)
		placeFood();

	//cout << endl<<"! END UPD, PRINT\n";
	printmap();
	
}

void Game::getInput() {
	key = Controls::NOKEY;
	while (_kbhit()) {
		char inp;
		
		inp = _getch();
		//cout << "FIRST " << (int)inp<<endl;
		// Код для стрелок
		if (inp == -32) {
			inp = _getch(); // Получение дополнительного кода для стрелок
			//cout << "SECOND " << inp << endl;
			switch (inp) {
			case 72: // Стрелка вверх
				key = Controls::U;
				break;
			case 80: // Стрелка вниз
				key = Controls::D;
				break;
			case 75: // Стрелка влево
				key = Controls::L;
				break;
			case 77: // Стрелка вправо
				key = Controls::R;
				break;
			}
		}
		else if (inp == 13) {
			key = Controls::E;
		}
		else {
			key = Controls::NOKEY;
		}
		
	}
}

bool Game::isInBounds(int x, int y) {
	return (x >= 0) && (y >= 0) && (x < sx) && (y < sy);
}

void Game::move(int fx, int fy, int tx, int ty, bool validate)
{
	//cout << "_TRY MOVE_" << tx << " " << ty << endl;
	if ((!validate) || (isInBounds(fx, fy) && isInBounds(tx, ty))) {
		//cout << "_MOVE_" <<tx<<" "<<ty << endl;
		
		gmap[ty][tx] = gmap[fy][fx];
		gmap[fy][fx] = nullptr;
		gmap[ty][tx]->x = tx;
		gmap[ty][tx]->y = ty;
	}
	else {
		//cout << "_CANT MOVE_" << endl;
	}
		
}

void Game::placeFood()
{
	bool occ = 1;
	int rx;
	int ry;
	while (occ) {
		rx = rand() % (sx - 4) + 2;
		ry = rand() % (sy - 4) + 2;
		occ = (bool)get(rx, ry);
	}
	create<Food>(rx, ry);
}

void Game::placeRandWalls(int count, int density)
{
	
	for (int i = 0;i < count;i++) {
		bool occ = 1;
		int rx;
		int ry;
		int tries = 0;
		while (occ) {
			tries++;
			occ = 0;
			rx = rand() % (sx - 4) + 2;
			ry = rand() % (sy - 4) + 2;
			occ = (bool)get(rx, ry);
			if(!occ && (rand()%101>=density))
				occ = get(rx + 1, ry) || get(rx - 1, ry) || get(rx, ry + 1) || get(rx, ry - 1) || get(rx + 1, ry + 1) || get(rx - 1, ry - 1) || get(rx - 1, ry + 1) || get(rx + 1, ry - 1);
			if (tries > 20)
				return;
		}

		//cout << "RANDWALL " << rx << " " << ry;
		create<Wall>(rx, ry);
	}
}

void Game::renderObj(shared_ptr<Gobject> o)
{
	SetConsoleTextAttribute(handle, o->color);
	cout << o->symbol;
}

void Game::gameloop() {
	state = 1;
	while (state) {
		
		update();
		Sleep(framedelay);
	}
}



void Game::cursorToZero()
{
	COORD newPosition;
	newPosition.X = 0; // column coordinate
	newPosition.Y = 0;  // row coordinate
	SetConsoleCursorPosition(handle, newPosition);
}

void Game::menuloop()
{
	int pos = 0;
	do {
		Setting& fset = settings[pos];
		cursorToZero();
		
		getInput();
		//cout << "KEY " << (int)key << endl;
		if (key != Controls::NOKEY)
			system("cls");

		if (key == Controls::U)
			pos--;
		if (key == Controls::D)
			pos++;
		if (pos < 0)
			pos = settingscount - 1;
		if (pos > settingscount-1)
			pos = 0;

		if (key == Controls::R) {
			if (fset.val + 1 <= fset.maxv)
				fset.val++;
		}
		if (key == Controls::L) {
			if (fset.val - 1 >= fset.minv)
				fset.val--;
		}
		for (int i = 0; i < settingscount;i++) {
			printSetting(settings[i], pos == i);
		}

	} while (key != Controls::E);

}

void Game::printSetting(Setting s, bool focus)
{
	if (!focus) {
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY);
		cout << s.name << " < " << s.val << " >\n";
	}
		
	else {
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
		cout << s.name << " < " << s.val << " > "<<s.desc<<endl;
	}
}


