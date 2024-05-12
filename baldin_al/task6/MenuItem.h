#pragma once

#include "Common.h"

class MenuItem {
public:
    string title;
    MenuFunction action;
    vector<MenuItem> subMenu;

    MenuItem(const string& t, MenuFunction a) : title(t), action(a) {}
    MenuItem(const string& t, const vector<MenuItem>& sm) : title(t), subMenu(sm), action(nullptr) {}

    bool hasSubMenu() const;
    bool hasAction() const;
};