#include "Map.h"

void Map::display() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cout << grid[y][x];
        }
        cout << '\n';
    }
}