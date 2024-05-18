#pragma once
#include <vector>
#include "Ship.h"

bool CheckShipsPlacement(const std::vector<Ship>& ships, int boardSize) {
    std::vector<int> mask(boardSize * boardSize, -1);

    for (int i = 0; i < ships.size(); ++i) {
        const Ship& ship = ships[i];

        for (int j = 0; j < ship.GetSize(); ++j) {
            int x = ship.GetX(j);
            int y = ship.GetY(j);
            if (x < 0 || x >= boardSize || y < 0 || y >= boardSize) return false;

            if (mask[x + y * boardSize] != -1) return false;
            mask[x + y * boardSize] = i;
        }
    }

    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            int val = mask[j + boardSize * i];
            if (val == -1) continue;

            for (int k = max(0, i - 1); k <= min(boardSize - 1, i + 1); ++k) {
                for (int l = max(0, j - 1); l <= min(boardSize - 1, j + 1); ++l) {
                    int val2 = mask[l + boardSize * k];
                    if (val2 != -1 && val2 != val) return false;
                }
            }
        }
    }

    return true;
}

std::vector<Ship> GenerateShips(int boardSize, std::initializer_list<int> sizes) {
    std::vector<Ship> res;
    do {
        res.clear();

        for (auto size : sizes) {
            int x = rand() % boardSize;
            int y = rand() % boardSize;
            int direction = rand() % 4;

            res.push_back(Ship(x, y, direction, size));
        }
    } while (!CheckShipsPlacement(res, boardSize));

    return res;
}