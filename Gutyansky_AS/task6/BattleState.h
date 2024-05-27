#pragma once
#include <vector>
#include "GameState.h"
#include "Engine.h"
#include "BattleshipGameData.h"
#include "ScreenBuffer.h"
#include "Player.h"
#include "Ship.h"
#include "IHumanMoveInput.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "ShipsRandomPlacement.h"
#include "Board.h"

class BattleState final : public GameState, public IHumanMoveInput {
private:
    BattleshipGameData* m_GameData;
    std::string m_Title;
    Board m_LeftBoard, m_RightBoard;
    Player* m_Players[2];

    int m_CurrentPlayer;

    bool m_AimShown;
    int m_AimX;
    int m_AimY;

    void DrawShips(Board& board, const std::vector<Ship>& ships) {
        for (const auto& ship : ships) {
            for (int i = 0; i < ship.GetSize(); ++i) {
                int x = ship.GetX(i);
                int y = ship.GetY(i);

                if (x < 0 || x >= board.GetSize() || y < 0 || y >= board.GetSize()) continue;

                char c = 'S';
                if (ship.IsDestroyed()) c = 'X';
                else if (ship.IsHit(i)) c = '*';

                board.SetChar(x, y, c);
            }
        }
    }

    void DrawMoves(Board& board, const std::map<std::pair<int, int>, MoveResult>& moves) {
        for (const auto& m : moves) {
            MoveResult res = m.second;
            char c = '.';
            if (res == MoveResult::Hit) c = 'H';
            else if (res == MoveResult::Destroy) c = 'X';

            board.SetChar(m.first.first, m.first.second, c);
        }
    }

    void DrawAim(Board& board) {
        for (int i = 0; i < board.GetSize(); ++i) {
            if (i == m_AimY) continue;

            board.SetChar(m_AimX, i, '|');
        }

        for (int j = 0; j < board.GetSize(); ++j) {
            if (j == m_AimX) continue;

            board.SetChar(j, m_AimY, '-');
        }
    }

    MoveResult HandleMove(std::pair<int, int> move, Player* player, Player* other) {
        auto& otherShips = other->GetShips();

        for (auto& ship : otherShips) {
            for (int i = 0; i < ship.GetSize(); ++i) {
                if (ship.GetX(i) == move.first && ship.GetY(i) == move.second) {
                    ship.TryHit(i);

                    if (!ship.IsDestroyed()) {
                        player->GetPreviousMoves()[move] = MoveResult::Hit;

                        return MoveResult::Hit;
                    }
                    else {
                        for (int j = 0; j < ship.GetSize(); ++j) {
                            player->GetPreviousMoves()[{ ship.GetX(j), ship.GetY(j) }] = MoveResult::Destroy;
                        }

                        return MoveResult::Destroy;
                    }
                }
            }
        }

        player->GetPreviousMoves()[move] = MoveResult::Fail;
        return MoveResult::Fail;
    }

    int GetDestroyedShipsCount(const std::vector<Ship>& ships) {
        int count = 0;
        for (auto ship : ships) {
            if (ship.IsDestroyed()) ++count;
        }

        return count;
    }
protected:
    void Draw(ScreenBuffer& screen) override {
        m_LeftBoard.Clear();
        m_RightBoard.Clear();

        DrawMoves(m_LeftBoard, m_Players[1]->GetPreviousMoves());
        DrawShips(m_LeftBoard, m_Players[0]->GetShips());

        DrawMoves(m_RightBoard, m_Players[0]->GetPreviousMoves());

        if (m_AimShown) {
            DrawAim(m_RightBoard);
        }

        screen.Printf(0, 0, m_Title.c_str());
        screen.Printf(0, 2, "w/a/s/d - move  h - shoot");
        screen.Printf(0, 4, "Your ships");
        screen.Printf(0, 5, "%d/%d destroyed", GetDestroyedShipsCount(m_Players[0]->GetShips()), m_Players[0]->GetShips().size());
        screen.Write(0, 6, m_LeftBoard.GetBuffer());
        screen.Printf(20, 4, "Your moves");
        screen.Printf(20, 5, "%d/%d destroyed", GetDestroyedShipsCount(m_Players[1]->GetShips()), m_Players[1]->GetShips().size());
        screen.Write(20, 6, m_RightBoard.GetBuffer());
    }
public:
    BattleState(BattleshipGameData* gameData, IEngine* game) : GameState(game), m_LeftBoard(gameData->GetBoardSize()), m_RightBoard(gameData->GetBoardSize()), 
        m_AimShown(false), m_AimX(0), m_AimY(0), m_GameData(gameData) { }

    int Run() override {
        m_Players[0] = new HumanPlayer(this, m_GameData->GetBoardSize(), m_GameData->GetPlayerShips());
        m_Players[1] = new AIPlayer(m_GameData->GetBoardSize(), GenerateShips(m_GameData->GetBoardSize(), {4, 3, 3, 2, 2, 2, 1, 1, 1, 1}));
        m_CurrentPlayer = 0;

        int ind = 0;
        while (1) {
            m_Title = (m_CurrentPlayer == 0 ? "Your turn" : "Other player turn");
            Redraw();
            auto move = m_Players[m_CurrentPlayer]->GetMove();
            MoveResult res = HandleMove(move, m_Players[m_CurrentPlayer], m_Players[1 - m_CurrentPlayer]);

            if (res == MoveResult::Fail) {
                m_Title += ": Miss";
            }
            else if (res == MoveResult::Hit) {
                m_Title += ": Hit";
            }
            else if (res == MoveResult::Destroy) {
                m_Title += ": Destroyed";
            }

            Redraw();
            GetEngine()->SleepMilliseconds(1500);

            m_CurrentPlayer = 1 - m_CurrentPlayer;

            if (GetDestroyedShipsCount(m_Players[1]->GetShips()) == m_Players[1]->GetShips().size()) {
                m_Title = "YOU WIN!!!";
                Redraw();
                GetEngine()->SleepMilliseconds(1500);
                break;
            }
            else if (GetDestroyedShipsCount(m_Players[0]->GetShips()) == m_Players[0]->GetShips().size()) {
                m_Title = "YOU LOST :(";
                Redraw();
                GetEngine()->SleepMilliseconds(1500);
                break;
            }
        }

        delete m_Players[0];
        delete m_Players[1];

        return -1;
    }

    void SetAimPosition(int x, int y) override {
        if (x < 0 || x >= m_GameData->GetBoardSize() || y < 0 || y >= m_GameData->GetBoardSize()) {
            throw "Can't set position out of board";
        }

        m_AimX = x;
        m_AimY = y;

        Redraw();
    }

    void ShowAim(bool show) override {
        m_AimShown = show;

        Redraw();
    }

    int GetInput() override {
        return GetEngine()->GetInput();
    }
};
