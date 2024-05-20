#pragma once

#define SETTINGS_COUNT 7

#include <vector>
#include <memory>
#include<string>
#include "windows.h"
using namespace std;

class ActiveGobject;

enum class Controls{NOKEY, U, R, D, L, E};

struct Setting {
    const char* name;
    int minv;
    int defaultv;
    int maxv;
    int* val;
    const char* desc;
};

class Game {
    friend class Gobject;
    vector<vector<shared_ptr<Gobject>>> gmap; //shared_ptr лучше использовать? метод s_ptr <GObj> create(x,y)
    vector<shared_ptr<ActiveGobject>> activeObjects;
    
    HANDLE handle;
    int state = 0;
    unsigned framedelay = 100;
    const int settingscount = SETTINGS_COUNT;
    static Setting settings[SETTINGS_COUNT];
    int sx = 0;
    int sy = 0;
    //SETTINGS
    int usersx;
    int usersy;
    int maxfood = 4;
    int wallcount;
    int walldensity;
    int gamespeed;
    int targetlen;

public:
    Game(HANDLE h) { initSettings(); handle = h; };
    int foodcount = 0;
    int snakelen = 1;
    template<typename T>
    shared_ptr<T> create(int x, int y);

    Controls key;
    void initSettings();
    void placeFood();
    void placeRandWalls(int count, int density);
    bool isInBounds(int x, int y);
    void buildMap();
    void renderObj(shared_ptr<Gobject> o);
    void cursorToZero();
    void printmap();
    void update();
    void getInput();
    void move(int fx, int fy, int tx, int ty, bool validate = false);
    shared_ptr<Gobject> get(int x, int y) { return gmap[y][x]; }
    void over() { state = 0; }
    void gameloop();
    void menuloop();
    void printSetting(Setting s, bool focus);

};

