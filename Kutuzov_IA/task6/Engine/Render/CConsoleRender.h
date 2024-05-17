#pragma once
#include "CGameRender.h"
#include "CWindow.h"


class CConsoleRender : public CGameRender
{
protected:
	int Res_X = 100;
	int Res_Y = 30;

// Rendering override
	virtual void RenderFrame();

public:
	CConsoleRender(CGame* InGame);
	~CConsoleRender();
};
