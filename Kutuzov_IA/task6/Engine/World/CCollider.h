#pragma once
#include "CScript.h"
#include "../Game/DataTypes.h"

class CCollider : public CScript
{
protected:
	TVector2D RelativePosition; // Position of the collider relative to the owner object

	bool Registered; // Whether the collider was registered in the world or not

	std::map<std::string, CCollider*> CurrentCollisions;

public:
	bool ReceivesCollision; // Does collider receive collision events
	bool CreatesCollision; // Does collider create collisions with other objects

protected:
	bool Created() override;

public:
	CCollider(CObject* Owner, std::string Name = "Collider");

	virtual ~CCollider();

	// Configuration
	void UpdateCollisionSettings(bool InReceivesCollision = true, bool InCreatesCollision = true);

	// Registering
	bool RegisterCollider();
	bool UnRegisterCollider();

	// Checks if collisions happen
	virtual bool CheckCollision(CCollider* OtherCollider);

	// Relative Position
	TVector2D GetRelativePosition();
	void SetRelativePosition(TVector2D& In_RelativePosition);

	// Global Position
	TVector2D GetGlobalPosition();

	// Current Collisions
	void AddCollision(CCollider* Collider);
	void RemoveCollision(CCollider* Collider);
	bool HasCollisionWith(CCollider* Collider);

};


class CRectangleCollider : public CCollider
{
protected:
	TVector2D Size;

private:
	bool CallCheckCollision(CRectangleCollider* Collider);
	bool CallCheckCollision(CCollider* Collider);

public:
	CRectangleCollider(CObject* Owner, std::string Name);

	virtual bool CheckCollision(CCollider* OtherCollider) override;

	// Size
	TVector2D GetSize();
	void SetSize(TVector2D& In_Size);

	// Sides
	float Left();
	float Right();
	float Top();
	float Bottom();
};
