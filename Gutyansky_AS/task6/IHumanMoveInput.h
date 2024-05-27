#pragma once

class IHumanMoveInput {
public:
    virtual ~IHumanMoveInput() = 0 {}

    virtual int GetInput() = 0;
    virtual void ShowAim(bool show) = 0;
    virtual void SetAimPosition(int x, int y) = 0;
};
