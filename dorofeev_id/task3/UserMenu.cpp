#include "UserMenu.h"

UserMenu::UserMenu(int num) : numCommands(num), lastSelected(-1) 
{
    menuItems.resize(num);
}

void UserMenu::setMenuItem(int index, const std::string& item)
{
    if (index >= 0 && index < numCommands) 
    {
        menuItems[index] = item;
    }
}

void UserMenu::printMenu(int startPosition, int offset) const 
{
    for (int i = 0; i < startPosition - 1; ++i) 
    {
        std::cout << std::endl;
    }
    for (int i = 0; i < numCommands; ++i) 
    {
        std::cout << std::string(offset, ' ') << i + 1 << ". " << menuItems[i] << std::endl;
    }
}

int UserMenu::selectMenuItem()
{
    int choice;
    std::cout << "Select a menu item: ";
    std::cin >> choice;

    if (choice >= 1 && choice <= numCommands) 
    {
        lastSelected = choice;
        return choice;
    }
    else
    {
        std::cout << "Error: invalid menu item selection!" << std::endl;
        return -1;
    }
}

int UserMenu::getLastSelected() const
{
    return lastSelected;
}

int UserMenu::getNumCommands() const
{
    return numCommands;
}
