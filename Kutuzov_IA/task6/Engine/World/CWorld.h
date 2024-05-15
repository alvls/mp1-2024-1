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

private:
	// Entity handling
	bool CallSpawn(CEntity* InEntity); // Spawns entity into the world
	bool CallSpawn(CObject* InObject); // Adds a new object into the world

public:
	CWorld(CGame* InGame);

	// Called every game frame
	float WorldUpdate(float DeltaTime);

	// Returns Game Instance pointer
	CGame* GetGame();

	// Spawning (for classes with defined CallSpawn)
	template <typename T> T* Spawn(std::string Name = "Entity");

	// Destruction
	bool Destroy(CEntity* InEntity); // Destroys entity in the world
	bool Destroy(CObject* InObject); // Destroys object in the world


	// Handling object collisions in the world
	void UpdateCollisions();
};
