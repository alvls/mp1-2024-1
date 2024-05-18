#pragma once
#include <vector>
#include <utility>
#include "Player.h"
#include "Ship.h"
#include "GameState.h"

class HumanPlayer final : public Player {
private:
    IHumanMoveInput* m_MoveInput;

    int m_AimX;
    int m_AimY;

public:
    HumanPlayer(IHumanMoveInput* moveInput, int boardSize, const std::vector<Ship>& ships) : Player(boardSize, ships), m_MoveInput(moveInput) {}

    std::pair<int, int> GetMove() override {
        m_MoveInput->ShowAim(true);

        m_AimX = 0;
        m_AimY = 0;

        while (true) {
            m_MoveInput->SetAimPosition(m_AimX, m_AimY);

            bool accepted = false;
            switch (m_MoveInput->GetInput()) {
            case 'a':
                --m_AimX;
                if (m_AimX < 0) m_AimX = 0;
                break;
            case 'd':
                ++m_AimX;
                if (m_AimX << 0 >= m_BoardSize) m_AimX = m_BoardSize - 1;
                break;
            case 'w':
                --m_AimY;
                if (m_AimY < 0) m_AimY = 0;
                break;
            case 's':
                ++m_AimY;
                if (m_AimY >= m_BoardSize) m_AimY = m_BoardSize - 1;
                break;

            case 'h':
                if (m_Moves.find({ m_AimX, m_AimY }) == m_Moves.end()) {
                    accepted = true;
                }
                break;
            }

            if (accepted) break;
        }

        m_MoveInput->ShowAim(false);

        return { m_AimX, m_AimY };
    }
};