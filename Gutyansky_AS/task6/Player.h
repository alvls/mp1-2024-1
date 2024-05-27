#pragma once
#include <vector>
#include <map>
#include <utility>
#include "Ship.h"
#include "MoveResult.h"

class Player {
protected:
    int m_BoardSize;
    std::vector<Ship> m_Ships;
    std::map<std::pair<int, int>, MoveResult> m_Moves;
public:
    Player(int boardSize, const std::vector<Ship>& ships) : m_Ships(ships), m_BoardSize(boardSize) { }
    virtual ~Player() = 0 {}

    std::vector<Ship>& GetShips() {
        return m_Ships;
    }

    std::map<std::pair<int, int>, MoveResult>& GetPreviousMoves() {
        return m_Moves;
    }

    virtual std::pair<int, int> GetMove() = 0;
};