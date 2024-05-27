#include "Menu.h"

void Menu::navigate() {
    char key;
    do {
        system("cls");
        for (int i = 0; i < items.size(); ++i) {
            if (i == selection) {
                cout << "\033[32m> " << items[i].title << " <\033[0m" << '\n';
            }
            else {
                cout << "  " << items[i].title << "\n";
            }
        }

        key = _getch();
        if (key == Up && selection > 0) {
            selection--;
        }
        else if (key == Down && selection < items.size() - 1) {
            selection++;
        }
        else if (key == 13) {
            if (items[selection].hasSubMenu()) {
                Menu subMenu(items[selection].subMenu);
                subMenu.navigate();
            }
            else if (items[selection].hasAction()) {
                items[selection].action();
            }
        }
    } while (key != Esc);
}