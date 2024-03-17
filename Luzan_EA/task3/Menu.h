#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <conio.h>

using namespace std;
enum TColor {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
    LIGHTMAGENTA, YELLOW, WHITE
};

enum TButtons {
    ARROW_UP = 72, ARROW_DOWN = 80, ENTER = 13
};

void clearScreen();

class Menu {
private:
    vector <string> v;
    int last_pos;

    void setLastChoice(unsigned lc);

public:
    Menu(int size);

    ~Menu();

    int getMenuSize();

    bool setItm(string itmName, int pos);

    void addItm(string itmName);

    int getLastChoice();

    void printLastChoice();

    void printMenu(int x, int y, int high_light);

    void getInp(int x, int y);
};