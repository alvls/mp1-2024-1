#include "Common.h"
#include "Menu.h"
#include "Game.h"
#include "Utils.h"

void startGame() {
    system("cls");
    srand(time(0));
    Game game;
    game.run();
}

void endProgram() {
    ClearGameResults(results_file);
    exit(0);
}

int main()
{
    setlocale(LC_ALL, "rus");

    try {
        if (!fileExists(settings_file))
            SetSetting(settings_file);

        vector<MenuItem> difficultyMenu;
        difficultyMenu.push_back(MenuItem("Easy", &changeDiff1));
        difficultyMenu.push_back(MenuItem("Medium", &changeDiff2));
        difficultyMenu.push_back(MenuItem("Hard", &changeDiff3));

        vector<MenuItem> settingsMenu;
        settingsMenu.push_back(MenuItem("Размер поля", &changeSize));
        settingsMenu.push_back(MenuItem("Символ змейки", &changeSnakeSymbol));
        settingsMenu.push_back(MenuItem("Символ стен", &changeWallSymbol));
        settingsMenu.push_back(MenuItem("Символ еды", &changeFoodSymbol));
        settingsMenu.push_back(MenuItem("Количество очков для победы", &changeWinSize));

        vector<MenuItem> mainMenu;
        mainMenu.push_back(MenuItem("Начать игру", &startGame));
        mainMenu.push_back(MenuItem("Уровень сложности", difficultyMenu));
        mainMenu.push_back(MenuItem("Таблица результатов", &ResultsTable));
        mainMenu.push_back(MenuItem("Настройки", settingsMenu));
        mainMenu.push_back(MenuItem("Выход", &endProgram));

        Menu menu(mainMenu);
        menu.navigate();

        system("pause");
    }
    catch (string s) {
        cout << s << '\n';
    }
}


