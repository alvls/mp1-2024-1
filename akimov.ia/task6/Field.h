#ifndef FIELD_H
#define FIELD_H

#include "GameObject.h"
#include <vector>

using namespace std;

const int N = 25; // ������ ���� ��� ����
const int M = 30; // ����� ���� ��� ����
const int WALL = -1; // ��������� ��� ������������� ����
const int FOOD = -2; // ��������� ��� ������������� ���

class Field : public GameObject
{
    vector<vector<int>> grid; // ����� ����
public:
    Field();
    void placeFood();
    void setCell(int x, int y, int value);
    int getCell(int x, int y) const;
    void update() override;
    void draw() override;
};

#endif