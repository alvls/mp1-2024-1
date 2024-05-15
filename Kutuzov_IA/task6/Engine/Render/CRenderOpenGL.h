#pragma once
#include "CGameRender.h"
#include "CWindow.h"

class CRenderOpenGL : public CGameRender
{
protected:
	CWindow* Window;

// Rendering override
	virtual void RenderFrame();

public:
	CRenderOpenGL(CGame* InGame);
	~CRenderOpenGL();
};

