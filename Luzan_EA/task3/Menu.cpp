#include "Menu.h"

using namespace std;


void Menu::setLastChoice(unsigned lc) {
    last_pos = lc;
}

Menu::Menu(int size) {
    v.resize(size);
    last_pos = -1;
}

Menu::~Menu() = default;

int Menu::getMenuSize() {
    return v.size();
}

bool Menu::setItm(string itmName, int pos) {
    if ((pos < 0) || (pos >= v.size())) {
        return false;
    }
    v[pos] = itmName;
    return true;
}

void Menu::addItm(string itmName) {
    v.push_back(itmName);
}

int Menu::getLastChoice() {
    return last_pos;
}

void Menu::printLastChoice() {
    if ((last_pos >= 0) && (last_pos < this->getMenuSize()))
        cout << "Last choice was: " << last_pos << endl;
    else
        cout << "Right choice hasn't been made yet" << endl;
}

void Menu::printMenu(int x = 0, int y = 0, int high_light = -1) {
    COORD pos{}; // {}
    HANDLE Console;
    Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        throw 1;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(Console, pos);
    int tmp = v.size();
    for (int i = 0; i < tmp; i++) {
        if (i == high_light) {
            CONSOLE_SCREEN_BUFFER_INFO buf;
            GetConsoleScreenBufferInfo(Console, &buf);
            SetConsoleTextAttribute(Console, GREEN);
            cout << v[i] << endl;
            SetConsoleTextAttribute(Console, buf.wAttributes);
        }
        else
            cout << v[i] << endl;
        pos.Y++;
        SetConsoleCursorPosition(Console, pos);
    }
}

void Menu::getInp(int x = 0, int y = 0) {
    bool flag = true;
    int user_choice = 0;
    int pressed_button = 0;
    this->setLastChoice(user_choice);
    int size_ = this->getMenuSize();
    do {
        this->printMenu(x, y, user_choice);
        pressed_button = _getch();
        switch (pressed_button) {
        case ARROW_DOWN:
            user_choice = (user_choice + 1) % size_;
            this->setLastChoice(user_choice);
            break;
        case ARROW_UP:
            user_choice = (user_choice - 1) % size_;
            if (user_choice < 0) { user_choice += size_; }
            this->setLastChoice(user_choice);
            break;
        case ENTER:
            flag = false;
            break;
        }
    } while (flag);
    //system("pause");
}
