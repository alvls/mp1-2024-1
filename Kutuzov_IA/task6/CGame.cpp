#include "CGame.h"
#include "CWorld.h"
#include "CGameRender.h"

using namespace std;

// CGame
CGame::CGame()
{
	GameWorld = new CWorld(this);
	GameRender = new CGameRender(this);
}

CGame::~CGame()
{
	delete GameWorld;
	delete GameRender;
}

void CGame::RunGame()
{
	Running = true;
	float DeltaTime = 0.f;

	while (Running)
	{
		DeltaTime = GameWorld->WorldUpdate(DeltaTime);
		DeltaTime += GameRender->Render();
	}
}

void CGame::QuitGame()
{
	Running = false;
}

