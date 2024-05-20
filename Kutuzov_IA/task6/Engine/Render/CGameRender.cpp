#include "CGameRender.h"
#include <chrono>

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
	auto TStart = chrono::high_resolution_clock::now();

	RenderFrame();

	auto TEnd = chrono::high_resolution_clock::now();

	float DeltaTime = float((chrono::duration_cast<chrono::milliseconds>(TEnd - TStart)).count()) / 1000.f;

	return DeltaTime;
}

void CGameRender::RenderFrame() {}
