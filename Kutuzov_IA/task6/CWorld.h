#pragma once
#include <vector>
#include <map>
#include <string>

class CGame;
class CEntity;
class CObject;


// Game world class, storing all Enitities in it
class CWorld
{
protected:
	CGame* Game;

	std::map<std::string, CEntity*> Entities; // List of all entities in the world

	// Collision lists
	std::vector<CObject*> CollisionReceivers;
	std::vector<CObject*> CollisionCreators;

	virtual void Update(float DetlaTime); // To override in child classes

public:
	CWorld(CGame* InGame);

	// Called every game frame
	float WorldUpdate(float DeltaTime);

	// Returns Game Instance pointer
	CGame* GetGame();

	// Entity handling
	// Spawns entity into the world
	bool SpawnEntity(CEntity* InEntity);
	// Destroys entity in the world
	bool DestroyEntity(CEntity* InEntity);

	// Adds a new object into the world
	bool AddObject(CObject* InObject);
	// Destroys object in the world
	bool DestroyObject(CObject* InObject);

	// Handling object collisions in the world
	void UpdateCollisions();
};
