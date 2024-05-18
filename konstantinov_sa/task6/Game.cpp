#include "Game.h"
#include <iostream>
#include "GameObjects.h"
#include <conio.h> //-
#include <windows.h> //-
using namespace std;

template<typename T>
inline shared_ptr<T> Game::create(int x, int y)
{
	return make_shared<T>(this, x, y);
}

void Game::buildMap(size_t sizex, size_t sizey) //матрица - массив строк
{
	sx = sizex + 2; sy = sizey + 2;
	gmap.resize(sy);
	for (auto& l : gmap) {
		l.resize(sx);
	}
	cout << "resize y = "<<gmap.size()<<" x = "<<gmap[0].size()<<endl;

	//for (size_t i = 0;i < sy;i++) {
	//	for (size_t j = 0;j < sx;j++) {
	//		gmap[i][j] = Air(this, j, i);
	//	}
	//}

	for (size_t i = 0;i < 2;i++) {
		for (size_t j = 0;j < sx;j++) {
			cout << "wall " << i << " " << j << endl;
			gmap[i][j] = create<Wall>(j,i);
		}
	}
	cout << "walls\n";
	gmap[sy - 1][sx - 1] = create<Wall>(sy - 1,sx - 1);
	gmap[4][4] = create<Snake>(4, 4);

}

void Game::printmap()
{
	cout << endl;
	for (size_t i = 0;i < sy;i++) {
		for (size_t j = 0;j < sx;j++) {
			if (gmap[i][j]) {
				cout << gmap[i][j]->symbol;
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

	for (size_t i = 0;i < sy;i++) {
		for (size_t j = 0;j < sx;j++) {
			if (gmap[i][j]) {
				cout << gmap[i][j]->symbol;
				gmap[i][j]->update();
			}
			else {
				cout << '-';
			}

		}
		cout << endl;
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

void Game::move(int fx, int fy, int tx, int ty)
{
	
	if (fx >= 0 && fy >= 0 && fx < sx && fy < sy && tx >= 0 && ty >= 0 && tx < sx && ty < sy) {
		cout << "_MOVE_" << endl;
		gmap[ty][tx] = gmap[fy][fx];
		gmap[fy][fx] = nullptr;
	}
	else {
		cout << "_CANT MOVE_" << endl;
	}
		
}


