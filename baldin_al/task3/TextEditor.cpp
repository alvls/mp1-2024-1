#include "TextEditor.h"

void TextEditor::setLen(unsigned int len_) {
    len = len_;
}

unsigned int TextEditor::getLen() {
    return len;
}

void TextEditor::setPos(short x, short y) {
    pos = { x, y };
}

COORD TextEditor::getPos() {
    return pos;
}

void TextEditor::place() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, { pos.X, pos.Y });
}

void TextEditor::setStr() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, { pos.X, pos.Y });
    string str;
    char ch;

    while (true) {
        ch = _getch();
        if (ch == '\r') {
            break;
        }
        else if (ch == '\b') {
            if (!str.empty()) {
                cout << "\b \b";
                str.pop_back();
            }
        }
        else if (str.size() < len) {
            str += ch;
            cout << ch;
        }
    }
    cout << '\n';
    input_str = str;
}

string TextEditor::getStr() {
    return input_str;
}