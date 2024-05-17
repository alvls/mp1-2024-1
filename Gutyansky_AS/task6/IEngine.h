#pragma once
#include "ScreenBuffer.h"
#include <string>

class IEngine {
public:
    virtual int GetInput() = 0;
    virtual ScreenBuffer& GetScreen() = 0;
    virtual void SleepMilliseconds(int time) = 0;
};