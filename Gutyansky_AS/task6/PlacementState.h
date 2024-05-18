#pragma once
#include "ShipsRandomPlacement.h"
#include "BattleshipGameStates.h"
#include "BattleshipGameData.h"
#include "GameState.h"
#include "Board.h"

class PlacementState final : public GameState {
private:
    BattleshipGameData* m_GameData;
    Board m_Board;
    std::vector<Ship> m_Ships;
    int m_SelectedShip;
    bool m_PlacementValid;

    void DrawShips(Board& board, const std::vector<Ship>& ships) {
        for (int i = 0; i < m_Ships.size(); ++i) {
            if (i == m_SelectedShip) continue;

            const Ship& ship = m_Ships[i];
            for (int j = 0; j < ship.GetSize(); ++j) {
                int x = ship.GetX(j);
                int y = ship.GetY(j);

                if (x < 0 || x >= board.GetSize() || y < 0 || y >= board.GetSize()) continue;
                board.SetChar(x, y, 'S');
            }
        }

        const Ship& ship = m_Ships[m_SelectedShip];
        for (int j = 0; j < ship.GetSize(); ++j) {
            int x = ship.GetX(j);
            int y = ship.GetY(j);

            if (x < 0 || x >= board.GetSize() || y < 0 || y >= board.GetSize()) continue;

            board.SetChar(x, y, (m_PlacementValid ? '+' : 'X'));
        }
    }
protected:
    void Draw(ScreenBuffer& screen) override {
        m_Board.Clear();

        DrawShips(m_Board, m_Ships);
        screen.Write(0, 0, m_Board.GetBuffer());
    }
public:
    PlacementState(BattleshipGameData* gameData, IEngine* engine) : GameState(engine), m_Board(gameData->GetBoardSize()), m_GameData(gameData) { }

    int Run() override {
        m_Ships = GenerateShips(m_GameData->GetBoardSize(), {4, 3, 3, 2, 2, 2, 1, 1, 1, 1});
        m_PlacementValid = true;
        m_SelectedShip = 0;

        while (1) {
            Redraw();
            
            switch (GetEngine()->GetInput()) {
            case 'k':
                if (m_PlacementValid) {
                    m_SelectedShip = (m_SelectedShip + 1) % m_Ships.size();
                }
                break;
            case 'j':
                if (m_PlacementValid) {
                    m_SelectedShip = (m_SelectedShip + m_Ships.size() - 1) % m_Ships.size();
                }
                break;
            case 'h':
                if (m_PlacementValid) {
                    m_GameData->SetPlayerShips(std::move(m_Ships));
                    return BattleshipGameStates::Battle;
                }
                break;
            case 'a': {
                Ship& ship = m_Ships[m_SelectedShip];
                ship.SetPosition(max(0, ship.GetX() - 1), ship.GetY());
                break;
            }
            case 'd': {
                Ship& ship = m_Ships[m_SelectedShip];
                ship.SetPosition(min(m_GameData->GetBoardSize() - 1, ship.GetX() + 1), ship.GetY());
                break;
            }
            case 'w': {
                Ship& ship = m_Ships[m_SelectedShip];
                ship.SetPosition(ship.GetX(), max(0, ship.GetY() - 1));
                break;
            }
            case 's': {
                Ship& ship = m_Ships[m_SelectedShip];
                ship.SetPosition(ship.GetX(), min(m_GameData->GetBoardSize() - 1, ship.GetY() + 1));
                break;
            }
            case 'e':
                m_Ships[m_SelectedShip].RotateRight();
                break;
            case 'q':
                m_Ships[m_SelectedShip].RotateLeft();
                break;
            }

            m_PlacementValid = CheckShipsPlacement(m_Ships, m_GameData->GetBoardSize());
        }

    }
};
