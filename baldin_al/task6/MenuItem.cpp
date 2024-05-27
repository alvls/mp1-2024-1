#include "MenuItem.h"

bool MenuItem::hasSubMenu() const { return !subMenu.empty(); }

bool MenuItem::hasAction() const { return action != nullptr; }