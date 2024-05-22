#pragma once
#include "Engine/ScarletEngine.h"

class CFruit : public CObject
{
	CRectangleCollider* MainCollider;

public:
	CFruit(CWorld* World, std::string Name);
	virtual ~CFruit() {}

	virtual void OnCollided(CCollider* OtherCollider, CCollider* Collider) override;
};

