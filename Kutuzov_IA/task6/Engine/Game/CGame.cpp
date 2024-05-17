#include "CGame.h"
#include "../World/CWorld.h"
#include "../Render/CGameRender.h"

using namespace std;

// CGame
CGame::CGame() 
{
	Camera = TCamera();
	GameName = "Game";

	GameWorld = nullptr;
	GameRender = nullptr;
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

string CGame::GetGameName() { return GameName; }

CWorld* CGame::GetWorld()
{
	return GameWorld;
}

CGameRender* CGame::GetRender()
{
	return GameRender;
}

TCamera& CGame::GetCamera()
{
	return Camera;
}

