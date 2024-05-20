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

	// Filling Free Tiles

	SnakeHead = Spawn<CSnakeHead>("Player");

	SpawnFruit();
}

void CSnakeWorld::Update(float DeltaTime)
{
}

void CSnakeWorld::SpawnFruit()
{
	int RandomIndex = rand() % FreeTilesList.size();
	CFruit* Fruit = Spawn<CFruit>("Fruit");

	std::set<TIntVector2D>::iterator It = my_set.begin();
	std::advance(It, RandomIndex);
	Fruit->SetPosition((*It) * TILE_SIZE);
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


// Tiles
void CSnakeWorld::OccupyTile(TIntVector2D& Tile)
{
	FreeTilesList.erase(Tile);
}

void CSnakeWorld::FreeTile(TIntVector2D& Tile)
{
	FreeTilesList.insert(Tile);
}

TIntVector2D CSnakeWorld::GetTile(TVector2D& Postion)
{
	return TIntVector2D(
		int(Position.X / TILE_SIZE),
		int(Position.Y) / TILE_SIZE
	);
}


// Borders
float CSnakeWorld::Left()
{
	return -1 * (SizeX / 2) * TILE_SIZE;
}

float CSnakeWorld::Right()
{
	return (SizeX / 2) * TILE_SIZE;
}

float CSnakeWorld::Top()
{
	return (SizeY / 2) * TILE_SIZE;
}

float CSnakeWorld::Bottom()
{
	return -1 * (SizeY / 2) * TILE_SIZE;
}