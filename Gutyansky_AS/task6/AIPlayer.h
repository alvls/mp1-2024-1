#pragma once
#include <vector>
#include "Player.h"
#include "Ship.h"

class AIPlayer final : public Player {
private:
    bool CheckPosition(std::pair<int, int> pos) {
        if (m_Moves.find(pos) != m_Moves.end()) return false;

        for (int i = max(0, pos.second - 1); i <= min(m_BoardSize - 1, pos.second + 1); ++i) {
            for (int j = max(0, pos.first - 1); j <= min(m_BoardSize - 1, pos.first + 1); ++j) {
                if (i == pos.second && j == pos.first) continue;

                auto it = m_Moves.find({ j, i });
                if (it != m_Moves.end() && it->second == MoveResult::Destroy) return false;
            }
        }

        return true;
    }

public:
    AIPlayer(int boardSize, const std::vector<Ship>& ships) : Player(boardSize, ships) { }

    std::pair<int, int> GetMove() override {    
        for (const auto& move : m_Moves) {
            if (move.second != MoveResult::Hit) continue;

            std::pair<int, int> pos = move.first;
            std::pair<int, int> best = { -1, -1 };
            bool rowFound = false;
            for (int i = max(0, pos.second - 1); i <= min(m_BoardSize - 1, pos.second + 1); ++i) {
                for (int j = max(0, pos.first - 1); j <= min(m_BoardSize - 1, pos.first + 1); ++j) {
                    if (i == pos.second && j == pos.first) continue;

                    if (CheckPosition({ j, i })) {
                        best = { j, i };
                        
                        std::pair<int, int> opposite = { 2 * pos.first - j, 2 * pos.second - i };
                        if (opposite.first >= 0 && opposite.second >= 0 && opposite.first < m_BoardSize && opposite.second < m_BoardSize) {
                            auto it = m_Moves.find(opposite);
                            if (it != m_Moves.end() && it->second == MoveResult::Hit) {
                                rowFound = true;
                            }
                        }
                    }

                    if (rowFound) break;
                }

                if (rowFound) break;
            }

            if (best.first != -1) return best;
        }

        std::pair<int, int> res;
        do {
            res = { rand() % m_BoardSize, rand() % m_BoardSize };
        } while (!CheckPosition(res));

        return res;
    }
};
