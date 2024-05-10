#include "ScreenBuffer.h"

int main()
{
    ScreenBuffer<25, 80> scrBuf;

    scrBuf.ShowCursor(false);

    char line[] = "+-------+";
    char empty[] = "+       +";
    for (int x = 0; x < 80 - sizeof(line)/sizeof(char); x++) {
        for (int y = 0; y < 21; y++) {
            scrBuf.Clear();

            scrBuf.Write(x, y, line, sizeof(line) - 1);
            scrBuf.Write(x, y + 1, empty, sizeof(empty) - 1);
            scrBuf.Printf(x, y + 2, "+ %02d-%02d +", x, y);
            scrBuf.Write(x, y + 3, empty, sizeof(empty) - 1);
            scrBuf.Write(x, y + 4, line, sizeof(line) - 1);

            scrBuf.Flush();

#ifdef _WIN32
            Sleep(30);
#else
            usleep(30000);
#endif //_WIN32
        }
    }
    getchar();
}