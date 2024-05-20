#include "CGame.h"
#include "../World/CWorld.h"
#include "../Render/CGameRender.h"
#include "CPlayerController.h"

#include <cmath>
#include <chrono>
#include <thread>


using namespace std;

// CGame
CGame::CGame() 
{
	Camera = TCamera();
	GameName = "Game";
	TargetFPS = 60.f;

	GameWorld = nullptr;
	GameRender = nullptr;
	PlayerController = nullptr;

	Running = false;
}

CGame::~CGame()
{
	delete GameWorld;
	delete GameRender;
	delete PlayerController;
}

void CGame::RunGame()
{
	if (!(GameWorld && GameRender && PlayerController))
		return;

	GameWorld->WorldInitCall();

	Running = true;
	float DeltaTime = 0.f;

	while (Running)
	{
		DeltaTime = GameWorld->WorldUpdate(DeltaTime);
		DeltaTime += GameRender->Render();

		float WaitTime = ((1 / TargetFPS) - DeltaTime) > 0 ? ((1 / TargetFPS) - DeltaTime) : 0.f;
		this_thread::sleep_for(chrono::milliseconds(int(WaitTime * 1000))); // Not consistent! Should deal with it at some point

		DeltaTime = DeltaTime < (1 / TargetFPS) ? (1 / TargetFPS) : DeltaTime;
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

CPlayerController* CGame::GetPlayerController()
{
	return PlayerController;
}

TCamera& CGame::GetCamera()
{
	return Camera;
}

