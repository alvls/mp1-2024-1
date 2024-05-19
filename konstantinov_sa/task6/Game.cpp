#include "Game.h"
#include <iostream>

#include <conio.h> //-
#include <windows.h> //-
using namespace std;

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

void Game::buildMap(size_t sizex, size_t sizey) //матрица - массив строк
{
	sx = sizex + 2; sy = sizey + 2;
	gmap.resize(sy);
	for (auto& l : gmap) {
		l.resize(sx);
	}
	cout << "resize y = "<<gmap.size()<<" x = "<<gmap[0].size()<<endl;

	for (size_t i = 0;i < 2;i++) {
		for (size_t j = 0;j < sx;j++) {
			cout << "wall " << i << " " << j << endl;
			gmap[i][j] = create<Wall>(j,i);
		}
	}
	cout << "walls\n";
	create<Wall>(4,6);
	create<Snake>(2, 2);

}

void Game::printmap()
{
	cout << endl;
	for (size_t i = 0;i < sy;i++) {
		for (size_t j = 0;j < sx;j++) {
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
	system("cls");
	cout << "UPDATE\n";
	getInput();
	cout << (int)key << endl;

	for (auto& obj : activeObjects) {
		cout << "ACTIVE UPD\n";
		obj->update();
	}

	cout << endl<<"END UPD, PRINT\n";
	printmap();
}

void Game::getInput() {
	if (_kbhit()) {
		


		int inp = _getch();
		cout << "FIRST " << inp<<endl;
		

		if (inp == 224) { // Код для стрелок
			inp = _getch(); // Получение дополнительного кода для стрелок
			cout << "SECOND " << inp << endl;
			switch (inp) {
			case 72: // Стрелка вверх
				key = Dir::U;
				break;
			case 80: // Стрелка вниз
				key = Dir::D;
				break;
			case 75: // Стрелка влево
				key = Dir::L;
				break;
			case 77: // Стрелка вправо
				key = Dir::R;
				break;
			}
		}
		
	}
	else {
		key = Dir::NOKEY;
	}
}

bool Game::isInBounds(int x, int y) {
	return (x >= 0) && (y >= 0) && (x < sx) && (y < sy);
}

void Game::move(int fx, int fy, int tx, int ty, bool validate)
{
	//cout << "_TRY MOVE_" << tx << " " << ty << endl;
	if ((!validate) || (isInBounds(fx, fy) && isInBounds(tx, ty))) {
		cout << "_MOVE_" <<tx<<" "<<ty << endl;
		
		gmap[ty][tx] = gmap[fy][fx];
		gmap[fy][fx] = nullptr;
		gmap[ty][tx]->x = tx;
		gmap[ty][tx]->y = ty;
	}
	else {
		cout << "_CANT MOVE_" << endl;
	}
		
}

void Game::renderObj(shared_ptr<Gobject> o)
{
	SetConsoleTextAttribute(handle, o->color);
	cout << o->symbol;
}


