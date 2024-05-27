#pragma once

#include "Common.h"
#include "MenuItem.h"

class Menu {
private:
    int selection = 0;
    vector<MenuItem> items;
public:
    Menu(const vector<MenuItem>& items_) : items(items_) {}

    void navigate();
};
