#ifndef FIELD_H
#define FIELD_H

#include "GameObject.h"
#include <vector>

using namespace std;

const int N = 25; // Ширина поля без стен
const int M = 30; // Длина поля без стен
const int WALL = -1; // Константа для представления стен
const int FOOD = -2; // Константа для представления еды

class Field : public GameObject
{
    vector<vector<int>> grid; // Сетка поля
public:
    Field();
    void placeFood();
    void setCell(int x, int y, int value);
    int getCell(int x, int y) const;
    void update() override;
    void draw() override;
};

#endif