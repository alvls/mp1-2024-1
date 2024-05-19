#include<iostream>
#include <conio.h> //-
#include <windows.h> //-
//#include<vector>
#include"GameObjects.h"
#include"Game.h"


using namespace std;


int main() {
	setlocale(LC_ALL, "rus");

    Game g;
    g.buildMap(10, 5);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    //cout << g.isInBounds(11, 5);
    //g.printmap();
    while (true) {
        if (_kbhit()) {


            g.update();
            
        }

    }

        
 

	//system("pause");
}