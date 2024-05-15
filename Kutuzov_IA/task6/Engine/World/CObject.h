#pragma once
#include "../Game/DataTypes.h"
#include "CEntity.h"
#include "CCollider.h"
#include <string>
#include <map>

class CEntity;
class CScript;

class CObject : public CEntity
{
protected:
	TVector2D Position; // Coordinates (top left corner)
	bool Visible; // Is Visible

	std::map<TVector2D, TSprite> Sprites; // Sprites that the object consists of with local offsets
	std::map<std::string, CScript*> Scripts; // Map of all the scripts attached to object


protected:
	virtual void OnCollided(CCollider* OtherCollider, CCollider* Collider);

private:
	bool CallAddScript(CScript* Script, std::string Name);
	bool CallAddCollider(CCollider* Collider);

public:
	CObject(CWorld* World, std::string Name = "Object");
	virtual ~CObject();

	// Position
	TVector2D GetPosition();
	void SetPosition(TVector2D& NewPosition);
	void Move(TVector2D& Offset);

	// Scripts
	template <typename T> T* AddScript(std::string Name);

	// Rendering
	bool IsVisible();

	// Collision
	template <typename T> T* AddCollider(std::string ColliderName);

	virtual void ReceivedCollision(CCollider* OtherCollider, CCollider* Collider);
	virtual void CreatedCollision(CCollider* OtherCollider, CCollider* Collider);

};
