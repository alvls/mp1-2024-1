#include<iostream>
#include <conio.h> //-
#include <windows.h> //-
//#include<vector>
#include"GameObjects.h"
#include"Game.h"


using namespace std;






int main() {
	setlocale(LC_ALL, "rus");

    //int lastChar = 0; // Переменная для хранения последнего нажатого символа

    //while (true) {
    //    if (_kbhit()) {
    //        lastChar = _getch(); // Получение последнего нажатого символа
    //        //system("cls"); // Очистка консоли
    //        std::cout << "Последний нажатый символ: " << lastChar << std::endl;
    //    }
    //}

    //return 0;

    Game g;
    g.buildMap(10, 5);
    //g.printmap();
    while (true) {
        if (_kbhit()) {


            g.update();
            Sleep(500);
        }

    }

        
 

	//system("pause");
}