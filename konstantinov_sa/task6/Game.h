#pragma once


#include <vector>
using namespace std;

class Gobject;

class Game {
    friend class Gobject;
    vector<vector<Gobject>> gmap;
    size_t sx = 0;
    size_t sy = 0;
public:
    void buildMap(size_t sizex, size_t sizey);
    void printmap();
};