#pragma once
#include <vector>
#include <algorithm>

class Ship {
private:
    int m_X, m_Y;
    int m_Size;
    int m_Direction;

    std::vector<bool> m_Hits;
    bool m_Destroyed;
public:
    Ship(int x, int y, int direction, int size) : m_X(x), m_Y(y), m_Direction(direction),
        m_Size(size), m_Hits(size), m_Destroyed(false) {
        if (direction < 0 || direction >= 4) {
            throw "Invalid ship direction. It must be in [0, 3]";
        }
    }

    void SetPosition(int x, int y) {
        m_X = x;
        m_Y = y;
    }

    void RotateRight() {
        m_Direction = (m_Direction + 1) % 4;
    }

    void RotateLeft() {
        m_Direction = (m_Direction + 3) % 4;
    }

    bool IsHit(int index) const {
        return m_Hits[index];
    }

    bool IsDestroyed() const {
        return m_Destroyed;
    }

    bool TryHit(int index) {
        if (m_Hits[index]) return false;

        m_Hits[index] = true;
        m_Destroyed = std::all_of(m_Hits.begin(), m_Hits.end(), [](bool v) { return v; });

        return true;
    }

    int GetX() const { return m_X; }

    int GetY() const { return m_Y; }

    int GetSize() const { return m_Size; }

    int GetDirection() const { return m_Size; }

    int GetX(int index) const {
        if (m_Direction == 0 || m_Direction == 2) return m_X;
        
        if (m_Direction == 1) return m_X + index;
        else return m_X - index;
    }

    int GetY(int index) const {
        if (m_Direction == 1 || m_Direction == 3) return m_Y;

        if (m_Direction == 0) return m_Y - index;
        else return m_Y + index;
    }

    int GetIndex(int x, int y) const {
        for (int i = 0; i < m_Size; ++i) {
            int ix = GetX(i);
            int iy = GetY(i);
            if (ix == x && iy == y) return i;
        }

        return -1;
    }
};