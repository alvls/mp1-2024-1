#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <conio.h> 
#include <locale>
#include <fstream>
#include <ctime>

using namespace std;

const int Up = 72;
const int Down = 80;
const int Left = 75;
const int Right = 77;
const int Enter = 13;
const int Esc = 27;

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

const string settings_file = "game_settings.txt";
const string results_file = "game_results.txt";

typedef void (*MenuFunction)();

struct point {
    int x, y;
    point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
};

struct GameResult {
    int width;
    int height;
    int score;
    double time;
    bool isWin;
    GameResult(int w = -1, int h = -1, int s = -1, float t = -1.0f, bool win = false)
        : width(w), height(h), score(s), time(t), isWin(win) {}
};