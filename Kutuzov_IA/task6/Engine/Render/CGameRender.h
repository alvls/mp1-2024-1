#pragma once
#include "../Game/DataTypes.h"
#include "../Game/CGame.h"

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

