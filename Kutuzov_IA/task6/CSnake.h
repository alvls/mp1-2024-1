#pragma once
#include "Engine/ScarletEngine.h"
#include "CSnakeWorld.h"

class CSnakeBody;

class CSnakeHead : public CObject, public CInputReceiver
{
	CSnakeWorld* SnakeWorld;

	TVector2D CurrentDirection;
	TVector2D InputDirection;
	float Speed;

	float DistanceSinceLastCheck;

	CRectangleCollider* MouthCollider;

	std::vector<CSnakeBody*> BodyList;

protected:
	virtual void ReceiveInput(int Input, char Action) override;
	virtual bool Created() override;
	virtual void Update(float DeltaTime) override;

	void SetInputDirection(TVector2D& NewDirection);
	void UpdateSprite();

public:
	CSnakeHead(CWorld* InWorld, std::string InName);
	virtual ~CSnakeHead();

	void AddSegment();
	void GameOver();

	void Victory();
};



class CSnakeBody : public CObject
{
	CSnakeHead* SnakeHead;
	int Index;
	CRectangleCollider* BodyCollider;

	TVector2D Direction;
	TIntVector2D CurrentTile;

protected:
	virtual void Update(float DeltaTime) override;

public:
	CSnakeBody(CWorld* InWorld, std::string InName);
	virtual ~CSnakeBody();

	void SpawnBody(CSnakeHead* InSnakeHead, int InIndex);

	virtual void OnCollided(CCollider* OtherCollider, CCollider* Collider) override;

	// Direction Interface
	TVector2D GetDirection();
	void SetDirection(TVector2D& NewDirection);

	// CurrentTile Interface
	TIntVector2D GetCurrentTile();
	void SetCurrentTile(TIntVector2D& NewTile);
};

