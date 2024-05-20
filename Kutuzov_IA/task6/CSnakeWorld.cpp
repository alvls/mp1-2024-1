#include "CSnakeWorld.h"
#include "CSnake.h"
#include "CFruit.h"
#include <random>

CSnakeWorld::CSnakeWorld(CGame* InGame) : CWorld(InGame)
{
}



void CSnakeWorld::InitWorld()
{
	srand(time(0));

	SnakeHead = Spawn<CSnakeHead>("Player");

	SpawnFruit();
}

void CSnakeWorld::Update(float DeltaTime)
{
}

void CSnakeWorld::SpawnFruit()
{
	TVector2D Position = TVector2D((rand() % SizeX) * TILE_SIZE - (SizeX * TILE_SIZE / 2), (rand() % SizeY) * TILE_SIZE - (SizeY * TILE_SIZE / 2));
	CFruit* Fruit = Spawn<CFruit>("Fruit");
	Fruit->SetPosition(Position);
}

void CSnakeWorld::ResetWorld()
{
	for (auto Object : Objects)
		if (Object.second != WorldScriptHandler)
			Destroy(Object.second);

	InitWorld();
}

void CSnakeWorld::FruitEaten()
{
	SpawnFruit();
	SnakeHead->AddSegment();
	SnakeHead->AddSegment();
	SnakeHead->AddSegment();
	SnakeHead->AddSegment();
}

void CSnakeWorld::GameOver()
{
	ResetWorld();
}
