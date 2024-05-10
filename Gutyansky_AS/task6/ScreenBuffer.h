#pragma once
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdarg>

#ifdef _WIN32
#include <windows.h>
#else // _WIN32
#include <unistd.h>
#endif

template <size_t Lines, size_t Chars>
class ScreenBuffer {
public:
    enum {
        Size = Lines * Chars
    };
private:
    size_t m_ScreenOffset;
    char   m_Screen[Size];

    static void ResetPosition() {
#ifdef _WIN32
        static COORD crd = {};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crd);
#else
        static char const toBegin[] = "\033[0;0H";
        std::fwrite(toBegin, sizeof(char), sizeof(toBegin) - 1, stdout);
#endif // _WIN32
    }

public:
    ScreenBuffer() {
        Clear();
    }

    void Flush() {
        ResetPosition();
        char preOut[Lines * (Chars + 1)];
        for (size_t line = 0; line < Lines; ++line) {
            std::memcpy(&preOut[line * (Chars + 1)], &m_Screen[line * Chars], Chars);
            preOut[line * (Chars + 1) + Chars] = '\n';
        }
        std::fwrite(preOut, sizeof(char), sizeof(preOut), stdout);
        std::fflush(stdout);
    }

    void ShowCursor(bool isShown) {
#ifdef _WIN32
        static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cci;
        GetConsoleCursorInfo(handle, &cci);
        cci.bVisible = isShown; // show/hide cursor
        SetConsoleCursorInfo(handle, &cci);
#else
        static char const showCmd[] = "\033[?25h";
        static char const hideCmd[] = "\033[?25l";
        std::fwrite((show ? showCmd : hideCmd), sizeof(char), sizeof(toBegin) - 1, stdout);
#endif // _WIN32
    }

    int Printf(char const* format, ...) {
        va_list args;
        va_start(args, format);
        const int remainLen = Size - m_ScreenOffset;
        const int r = std::vsnprintf(&m_Screen[m_ScreenOffset], remainLen, format, args);
        m_ScreenOffset += r;
        va_end(args);
        return r;
    }

    int Printf(int x, int y, char const* format, ...) {
        va_list args;
        va_start(args, format);
        if (x < 0 || x >= Chars || y < 0 || y >= Lines) return 0;

        char* end = &m_Screen[x + y * Chars];
        char* begin = &m_Screen[0];
        const int remainLen = Size - std::distance(begin, end);
        const int r = std::vsnprintf(end, remainLen, format, args);
        va_end(args);
        return r;
    }

    int Write(char const* data, size_t len) {
        const int remainLen = Size - m_ScreenOffset;
        const int count = len > remainLen ? remainLen : len;
        std::memcpy(&m_Screen[m_ScreenOffset], data, count);
        m_ScreenOffset += count;
        return count;
    }

    int Write(int x, int y, char const* data, size_t len) {
        if (x < 0 || x >= Chars || y < 0 || y >= Lines) return 0;

        char* end = &m_Screen[x + y * Chars];
        char* begin = &m_Screen[0];
        const int remainLen = Size - std::distance(begin, end);
        const int count = len > remainLen ? remainLen : len;
        std::memcpy(end, data, count);
        return count;
    }

    void Clear() {
        m_ScreenOffset = 0;
        std::memset(m_Screen, ' ', Size);
    }
};