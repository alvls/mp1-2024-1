#pragma once
#include "Engine/ScarletEngine.h"

#define TILE_SIZE 100

class CSnakeHead;

class CSnakeWorld : public CWorld
{
	int SizeX = 10, SizeY = 10;

	CSnakeHead* SnakeHead;

protected:
	virtual void InitWorld() override;
	virtual void Update(float DeltaTime) override;
	void SpawnFruit();

	void ResetWorld();

public:
	CSnakeWorld(CGame* InGame);

	void FruitEaten();
	void GameOver();
};

