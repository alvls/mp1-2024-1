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
        settingsMenu.push_back(MenuItem("������ ����", &changeSize));
        settingsMenu.push_back(MenuItem("������ ������", &changeSnakeSymbol));
        settingsMenu.push_back(MenuItem("������ ����", &changeWallSymbol));
        settingsMenu.push_back(MenuItem("������ ���", &changeFoodSymbol));
        settingsMenu.push_back(MenuItem("���������� ����� ��� ������", &changeWinSize));

        vector<MenuItem> mainMenu;
        mainMenu.push_back(MenuItem("������ ����", &startGame));
        mainMenu.push_back(MenuItem("������� ���������", difficultyMenu));
        mainMenu.push_back(MenuItem("������� �����������", &ResultsTable));
        mainMenu.push_back(MenuItem("���������", settingsMenu));
        mainMenu.push_back(MenuItem("�����", &endProgram));

        Menu menu(mainMenu);
        menu.navigate();

        system("pause");
    }
    catch (string s) {
        cout << s << '\n';
    }
}


