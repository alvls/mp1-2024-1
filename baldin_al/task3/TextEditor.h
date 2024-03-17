#pragma once
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class TextEditor {
    unsigned int len;
    COORD pos;
    string input_str;

public:
    TextEditor(short x_ = 0, short y_ = 0, int len_ = 0) {
        len = len_;
        pos = { x_, y_ };
    }

    void setLen(unsigned int len_);

    unsigned int getLen();

    void setPos(short x, short y);

    COORD getPos();

    void place();

    void setStr();

    string getStr();
};
