#include<iostream>
#include <conio.h> //-
#include <windows.h> //-
//#include<vector>
#include"GameObjects.h"
#include"Game.h"

//
// Возможно требуется не ниже C++17 
//

using namespace std;


int main() {
	setlocale(LC_ALL, "rus");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(h, &cursorInfo);

    // Hide the cursor
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(h, &cursorInfo);

    Game g(h);
    while (true) {
        g.menuloop();
        g.buildMap();
        g.gameloop();
    }
 

	//system("pause");
}