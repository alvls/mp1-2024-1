#pragma once
#include "CScript.h"
#include "../Game/DataTypes.h"

class CCollider : public CScript
{
protected:
	TVector2D RelativePosition; // Position of the collider relative to the owner object

	bool Registered; // Whether the collider was registered in the world or not

public:
	bool ReceivesCollision; // Does collider receive collision events
	bool CreatesCollision; // Does collider create collisions with other objects

public:
	CCollider(CObject* Owner, std::string Name = "Collider", TVector2D& In_RelativePosition = TVector2D());

	virtual ~CCollider();

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

};


class CRectangleCollider : public CCollider
{
protected:
	TVector2D Size;

private:
	bool CallCheckCollision(CRectangleCollider* Collider);
	bool CallCheckCollision(CCollider* Collider);

public:
	CRectangleCollider(CObject* Owner, std::string Name, TVector2D& In_RelativePosition = TVector2D(), TVector2D In_Size = TVector2D());

	virtual bool CheckCollision(CCollider* OtherCollider) override;

	// Size
	TVector2D GetSize();
	void SetSize(TVector2D& In_Size);
};
