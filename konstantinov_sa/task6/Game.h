#pragma once

#define SETTINGS_COUNT 7
//#include"GameObjects.h"
#include <vector>
#include <memory>
#include<string>
#include "windows.h"
using namespace std;

class ActiveGobject;
class Gobject;

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
    friend class Snake;
    friend class Segment;
    friend class Food;
    vector<vector<shared_ptr<Gobject>>> gmap;
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
    int foodcount = 0;
    int snakelen = 1;

    Controls key;
    void initSettings();
    void placeFood();
    void placeRandWalls(int count, int density);
    template<typename T>
    shared_ptr<T> create(int x, int y);
    void renderObj(shared_ptr<Gobject> o);
    void cursorToZero();
    void printmap();
    void update();
    void getInput();
    void move(int fx, int fy, int tx, int ty, bool validate = false);
    void over() { state = 0; }
    void printSetting(Setting s, bool focus);
    const shared_ptr<Gobject>& get(int x, int y) { return gmap[y][x]; }
public:
    Game(HANDLE h) { initSettings(); handle = h; };
    const Controls& getKey() { return key; }
    bool isInBounds(int x, int y);
    void buildMap();
    void gameloop();
    void menuloop();
};

