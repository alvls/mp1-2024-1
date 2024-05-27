#pragma once
#include "ScreenBuffer.h"

class IEngine {
public:
    virtual ~IEngine() = 0 {}

    virtual int GetInput() = 0;
    virtual ScreenBuffer& GetScreen() = 0;
    virtual void SleepMilliseconds(int time) = 0;
};