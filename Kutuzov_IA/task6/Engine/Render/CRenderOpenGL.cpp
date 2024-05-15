#include "CRenderOpenGL.h"
#include "Windows.h"

using namespace std;

CRenderOpenGL::CRenderOpenGL(CGame* InGame): CGameRender(InGame) 
{
	Window = new CWindow("Game");
}

CRenderOpenGL::~CRenderOpenGL()
{
	delete Window;
}

void CRenderOpenGL::RenderFrame()
{
	if (!Window->ProcessMessages())
		Game->QuitGame();

	// Rendering stuff
	Sleep(100);
}
