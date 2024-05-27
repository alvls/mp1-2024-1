#pragma once
#include <vector>
#include <string>

class Board final {
private:
    int m_Size;
    std::vector<std::string> m_Buffer;
public:
    Board(int size) : m_Size(size), m_Buffer(size + 2, std::string(size + 2, ' ')) {
        for (int i = 1; i < m_Buffer.size() - 1; ++i) {
            m_Buffer[i][0] = '|';
            m_Buffer[i].back() = '|';
        }

        m_Buffer[0].assign(size + 2, '-');
        m_Buffer.back().assign(size + 2, '-');
    }

    int GetSize() const {
        return m_Size;
    }

    const std::vector < std::string>& GetBuffer() const {
        return m_Buffer;
    }

    void Clear() {
        for (int i = 1; i < m_Size + 1; ++i) {
            for (int j = 1; j < m_Size + 1; ++j) {
                m_Buffer[i][j] = ' ';
            }
        }
    }

    void SetChar(int x, int y, char c) {
        if (x < 0 || x >= m_Size || y < 0 || y >= m_Size) {
            throw "Can't draw out of board";
        }
        m_Buffer[y + 1][x + 1] = c;
    }
};
