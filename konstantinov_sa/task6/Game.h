#pragma once


#include <vector>
#include <memory>

#include "windows.h"
using namespace std;

class ActiveGobject;

enum class Controls{NOKEY, U, R, D, L, E};

class Game {
    friend class Gobject;
    vector<vector<shared_ptr<Gobject>>> gmap; //shared_ptr лучше использовать? метод s_ptr <GObj> create(x,y)
    vector<shared_ptr<ActiveGobject>> activeObjects;
    size_t sx = 0;
    size_t sy = 0;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    int state = 0;
    unsigned framedelay = 1000;
    

public:
    int maxfood = 1;
    int foodcount = 0;
    int snakelen = 1;
    template<typename T>
    shared_ptr<T> create(int x, int y);

    Controls key;
    void placeFood();
    void Game::placeRandWalls(int count, int density);
    bool isInBounds(int x, int y);
    void buildMap(size_t sizex, size_t sizey);
    void renderObj(shared_ptr<Gobject> o);
    void printmap();
    void update();
    void getInput();
    void move(int fx, int fy, int tx, int ty, bool validate = false);
    shared_ptr<Gobject> get(int x, int y) { return gmap[y][x]; }
    void over() { state = 0; }
    void gameloop();


};


