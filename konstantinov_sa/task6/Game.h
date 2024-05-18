﻿#pragma once


#include <vector>
#include <memory>
using namespace std;

class Gobject;

enum class Dir{NOKEY, U, R, D, L};

class Game {
    friend class Gobject;
    vector<vector<shared_ptr<Gobject>>> gmap; //shared_ptr лучше использовать? метод s_ptr <GObj> create(x,y)
    size_t sx = 0;
    size_t sy = 0;
    

    template<typename T>
    shared_ptr<T> create(int x, int y);
public:
    Dir key;
    void buildMap(size_t sizex, size_t sizey);
    void printmap();
    void update();
    void getInput();
    void move(int fx, int fy, int tx, int ty);
    const Gobject& get(int x, int y) { return *gmap[y][x]; }


};


