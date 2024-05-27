#pragma once
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdarg>

#ifdef _WIN32
#include <windows.h>
#else // _WIN32
#include <unistd.h>
#endif
#include <string>

class ScreenBuffer {
private:
    size_t m_Width, m_Height;
    size_t m_ScreenOffset;
    char* m_Screen;
    char* m_PreOut;

    size_t GetBufferLength() const {
        return m_Width * m_Height;
    }

    size_t GetOutLength() const {
        return m_Height * (m_Width + 1);
    }

    static void ResetPosition();

public:
    ScreenBuffer(size_t width, size_t height) : m_Width(width), m_Height(height) {
        m_Screen = new char[GetBufferLength()];
        m_PreOut = new char[GetOutLength()];
        Clear();
    }

    ~ScreenBuffer() {
        delete[] m_Screen;
        delete[] m_PreOut;
    }

    size_t GetWidth() const {
        return m_Width;
    }

    size_t GetHeight() const {
        return m_Height;
    }

    void Clear() {
        m_ScreenOffset = 0;
        std::memset(m_Screen, ' ', GetBufferLength());
    }

    void Flush();
    void ShowCursor(bool isShown);
    int Printf(char const* format, ...);
    int Printf(int x, int y, char const* format, ...);
    int Write(char const* data, size_t len);
    int Write(int x, int y, char const* data, size_t len);
    int Write(int x, int y, const std::vector<std::string>& sprite);
};