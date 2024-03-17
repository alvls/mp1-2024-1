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
    getline(cin, str);
    if (str.length() > len) {
        str = str.substr(0, len);
    }
    input_str = str;
}

string TextEditor::getStr() {
    return input_str;
}