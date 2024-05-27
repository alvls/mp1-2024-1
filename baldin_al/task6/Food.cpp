#include "Food.h"

void Food::relocate(int width, int height, const Snake& snake) {
    bool isOccupied = true;
    do {
        isOccupied = false;
        position.x = 1 + rand() % (width - 2);
        position.y = 1 + rand() % (height - 2);
        for (const point& part : snake.getBody()) {
            if (position.x == part.x && position.y == part.y) {
                isOccupied = true;
                break;
            }
        }
    } while (isOccupied);
}