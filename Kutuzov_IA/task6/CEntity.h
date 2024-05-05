#pragma once
#include <string>
#include <vector>

class CGame;
class CWorld;

// Entitiy class is the base for every other class
class CEntity
{
protected:
	CWorld* World;
	std::string EntityWorldID; // Id of the entity in the world, handled automatically
	std::vector<std::string> Tags; // Entity tags

public:
	std::string Name; // Name of the entity, doesn't have to be unique

public:
	CEntity(CWorld* InWorld = nullptr);
	virtual ~CEntity();

	// Returns world pointer
	CWorld* GetWorld();

	// Returns ID in the world
	std::string GetEntityWorldID();

	// Returns Game Instance pointer
	CGame* GetGame();

	// Called when entity is spawned into the game
	bool EntityCreated(std::string WorldID, CWorld* WorldOverride = nullptr);
	virtual bool Created(); // To override in child classes

	// Called every game frame
	void EntityUpdate(float DeltaTime);
	virtual void Update(float DeltaTime); // To override in child classes+

	// Tags
	void AddTag(std::string& Tag);
	bool HasTag(std::string& Tag);
};

