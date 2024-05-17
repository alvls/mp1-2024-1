#include "ScreenBuffer.h"

void ScreenBuffer::ResetPosition() {
#ifdef _WIN32
    static COORD crd = {};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crd);
#else
    static char const toBegin[] = "\033[0;0H";
    std::fwrite(toBegin, sizeof(char), sizeof(toBegin) - 1, stdout);
#endif // _WIN32
}

void ScreenBuffer::Flush() {
    ResetPosition();
    for (size_t line = 0; line < m_Height; ++line) {
        std::memcpy(&m_PreOut[line * (m_Width + 1)], &m_Screen[line * m_Width], m_Width);
        m_PreOut[line * (m_Width + 1) + m_Width] = '\n';
    }
    std::fwrite(m_PreOut, sizeof(char), GetOutLength(), stdout);
    std::fflush(stdout);
}

void ScreenBuffer::ShowCursor(bool isShown) {
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

int ScreenBuffer::Printf(char const* format, ...) {
    va_list args;
    va_start(args, format);
    const int remainLen = GetBufferLength() - m_ScreenOffset;
    const int r = std::vsnprintf(&m_Screen[m_ScreenOffset], remainLen, format, args);
    m_ScreenOffset += r;
    va_end(args);
    return r;
}

int ScreenBuffer::Printf(int x, int y, char const* format, ...) {
    va_list args;
    va_start(args, format);
    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height) return 0;

    char* end = &m_Screen[x + y * m_Width];
    char* begin = &m_Screen[0];
    const int remainLen = GetBufferLength() - std::distance(begin, end);
    const int r = std::vsnprintf(end, remainLen, format, args);
    va_end(args);
    return r;
}

int ScreenBuffer::Write(char const* data, size_t len) {
    const int remainLen = GetBufferLength() - m_ScreenOffset;
    const int count = len > remainLen ? remainLen : len;
    std::memcpy(&m_Screen[m_ScreenOffset], data, count);
    m_ScreenOffset += count;
    return count;
}

int ScreenBuffer::Write(int x, int y, char const* data, size_t len) {
    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height) return 0;

    char* end = &m_Screen[x + y * m_Width];
    char* begin = &m_Screen[0];
    const int remainLen = GetBufferLength() - std::distance(begin, end);
    const int count = len > remainLen ? remainLen : len;
    std::memcpy(end, data, count);
    return count;
}

int ScreenBuffer::Write(int x, int y, std::vector<char const*> sprite)
{
    size_t total = 0;
    for (size_t i = 0; i < sprite.size(); ++i) {
        if (y + i < 0 || y + i >= m_Height) continue;

        size_t len = strlen(sprite[i]);
        for (size_t j = 0; j < len; ++j) {
            if (x + j < 0 || x + j >= m_Width) continue;

            m_Screen[(x + j) + (i + y) * m_Width] = sprite[i][j];
            ++total;
        }
    }
    return total;
}
