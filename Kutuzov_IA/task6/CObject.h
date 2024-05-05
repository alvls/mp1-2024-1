#pragma once
#include "DataTypes.h"
#include "CEntity.h"
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
	TRectangleCollider Collider; // Collider of the object

	std::map<std::string, CScript*> Scripts; // Map of all the scripts attached to object

public:
	bool ReceivesCollision; // Does object receive collision events
	bool CreatesCollision; // Does ojbect create collisions with other objects


protected:
	virtual void OnCollided(CObject* CollidingObject);

public:
	CObject(CWorld* World);
	virtual ~CObject();

	virtual bool Created();

	// Scripts
	bool AddScript(CScript* Script, std::string NameOverride = "-");
	bool ExecuteScript(std::string ScriptName);

	// Rendering
	bool IsVisible();
	void Render();

	// Collision
	bool CheckCollisionWithAnotherObject(CObject* OtherObject);

	virtual void ReceivedCollision(CObject* CollidingObject);
	virtual void CreatedCollision(CObject* CollidingObject);

};
