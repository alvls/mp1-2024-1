#pragma once
#include <vector>
#include "Ship.h"

class BattleshipGameData final {
private:
    int m_BoardSize;
    std::vector<Ship> m_PlayerShips;
public:
    BattleshipGameData(int boardSize) : m_BoardSize(boardSize) { }

    int GetBoardSize() const {
        return m_BoardSize;
    }

    void SetPlayerShips(const std::vector<Ship>& playerShips) {
        m_PlayerShips = playerShips;
    }

    std::vector<Ship>& GetPlayerShips() {
        return m_PlayerShips;
    }
};
