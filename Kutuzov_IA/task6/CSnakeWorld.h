#pragma once
#include "Engine/ScarletEngine.h"

#include <set>

#define TILE_SIZE 100

class CSnakeHead;

class CSnakeWorld : public CWorld
{
	int SizeX = 10, SizeY = 10;
	std::set<TIntVector2D> FreeTilesList;

	CSnakeHead* SnakeHead;

protected:
	virtual void InitWorld() override;
	virtual void Update(float DeltaTime) override;
	void SpawnFruit();

	void ResetWorld();

public:
	CSnakeWorld(CGame* InGame, int N, int M);

	void FruitEaten();
	void GameOver();

	// Tiles
	void OccupyTile(TIntVector2D& Tile);
	void FreeTile(TIntVector2D& Tile);

	TIntVector2D GetTile(TVector2D& Postion);

	// Borders
	float Left();
	float Right();
	float Top();
	float Bottom();
	
};

