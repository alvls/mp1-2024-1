#include "CGameRender.h"

using namespace std;


CGameRender::CGameRender(CGame* InGame)
{
	if (InGame)
		Game = InGame;

	else
		throw (exception("Invalid Game pointer!"));
}

CGameRender::~CGameRender()
{

}

float CGameRender::Render()
{
	RenderFrame();
	return 0.016f;
}

void CGameRender::RenderFrame() {}
