#include "Game.h"
#include <iostream>
#include "GameObjects.h"
using namespace std;


void Game::buildMap(size_t sizex, size_t sizey) //матрица - массив строк
{
	sx = sizex + 2; sy = sizey + 2;
	Game* Gobject::gamep = this;
	gmap.resize(sy);
	for (auto& l : gmap) {
		l.resize(sx);
	}
	cout << "resize y = "<<gmap.size()<<" x = "<<gmap[0].size()<<endl;
	for (size_t i = 0;i < 2;i++) {
		for (size_t j = 0;j < sx;j++) {
			cout << "wall " << i << " " << j << endl;
			gmap[i][j] = Wall();
		}
	}
	cout << "walls\n";
	gmap[sy - 1][sx - 1] = Wall();

}

void Game::printmap()
{
	for (size_t i = 0;i < sy;i++) {
		for (size_t j = 0;j < sx;j++) {
			cout<<gmap[i][j].symbol;
		}
		cout << endl;
	}
}
