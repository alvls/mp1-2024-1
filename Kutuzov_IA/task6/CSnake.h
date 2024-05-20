#pragma once
#include "Engine/ScarletEngine.h"
#include "CSnakeWorld.h"

class CSnakeBody;

class CSnakeHead : public CObject, public CInputReceiver
{
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
	void AddSegment();
	void GameOver();
};


class CSnakeBody : public CObject
{
	CSnakeHead* SnakeHead;
	int Index;
	CRectangleCollider* BodyCollider;

public:
	TVector2D Direction;
	TVector2D NextDirection;

protected:
	virtual void Update(float DeltaTime) override;

public:
	CSnakeBody(CWorld* InWorld, std::string InName);
	void SpawnBody(CSnakeHead* InSnakeHead, int InIndex);

	virtual void OnCollided(CCollider* OtherCollider, CCollider* Collider) override;
};

