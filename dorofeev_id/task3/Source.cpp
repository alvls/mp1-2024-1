#include "UserMenu.h"
int main() 
{
    UserMenu menu(3);

    menu.setMenuItem(0, "Item 1");
    menu.setMenuItem(1, "Item 2");
    menu.setMenuItem(2, "Item 3");

    int startPosition;
    std::cout << "Enter the starting position to display the menu (line number): ";
    std::cin >> startPosition;

    int offset;
    std::cout << "Enter the horizontal offset for the menu: ";
    std::cin >> offset;

    menu.printMenu(startPosition, offset);

    int choice = menu.selectMenuItem();
    if (choice != -1)
    {
        std::cout << "You selected item " << choice << std::endl;
        std::cout << "Number of the last selected item: " << menu.getLastSelected() << std::endl;
    }

    return 0;
}