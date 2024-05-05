#pragma once
#include "DataTypes.h"
#include "CGame.h"

class CGameRender
{
protected:
	CGame* Game;

// Actual rendering of the frame
	virtual void RenderFrame();

public:
	CGameRender(CGame* InGame);
	virtual ~CGameRender();

	// Render Frame Call, returns delta T
	float Render();

};

