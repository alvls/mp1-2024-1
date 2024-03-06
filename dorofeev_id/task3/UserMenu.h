#pragma once

#include <string>
#include <vector>
#include <iostream>

class UserMenu 
{
private:
    int numCommands;
    std::vector<std::string> menuItems;
    int lastSelected;

public:
    UserMenu(int num);

    void setMenuItem(int index, const std::string& item);
    void printMenu(int startPosition, int offset) const;
    int selectMenuItem();
    int getLastSelected() const;
    int getNumCommands() const;
};

