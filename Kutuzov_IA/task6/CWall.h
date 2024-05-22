#pragma once
#include "Engine/ScarletEngine.h"

class CWall : public CObject
{
	CRectangleCollider* Collider;
public:
	CWall(CWorld* World, std::string Name);

	void SetSize(TVector2D InSize);

	virtual void OnCollided(CCollider* OtherCollider, CCollider* Collider) override;
};

