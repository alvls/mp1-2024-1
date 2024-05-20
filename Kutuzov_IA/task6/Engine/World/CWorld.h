#pragma once
#include <vector>
#include <map>
#include <string>

class CGame;
class CEntity;
class CObject;
class CScript;
class CWorldScriptHandler;
class CCollider;


// Game world class, storing all Enitities in it
class CWorld
{
protected:
	CGame* Game;

	CWorldScriptHandler* WorldScriptHandler;

	std::map<std::string, CEntity*> Entities; // List of all entities in the world

	// Rendering Layers
	std::map<int, std::vector<CObject*>> RenderLayers;

	// Collision lists
	std::map<std::string, CCollider*> CollisionReceivers;
	std::map<std::string, CCollider*> CollisionCreators;

	// Destructio  List
	std::vector<CEntity*> DestructionList;

protected:

	virtual void InitWorld(); // Called when the game starts
	virtual void Update(float DetlaTime); // To override in child classes

private:
	// Entity handling
	bool CallSpawn(CEntity* InEntity); // Spawns entity into the world
	bool CallSpawn(CObject* InObject); // Adds a new object into the world

	// Destruction
	bool CallDestroy(CEntity* InEntity); // Destroys entity in the world
	bool CallDestroy(CObject* InObject); // Destroys object in the world

public:
	CWorld(CGame* InGame);
	virtual ~CWorld();

	// Initializes the world
	void WorldInitCall();

	// Called every game frame
	float WorldUpdate(float DeltaTime);

	// Returns Game Instance pointer
	CGame* GetGame();

	// Returns World Script Handler
	CWorldScriptHandler* GetWorldScriptHandler();

	// Spawning (for classes with defined CallSpawn)
	template <typename T> T* Spawn(std::string Name = "Entity")
	{
		T* NewObject = new T(this, GenerateUniqueEntityName(Name));
		if (CallSpawn(NewObject))
			return NewObject;

		else
		{
			delete NewObject;
			return nullptr;
		}
	}

	// Destruction
	// Handling destruction
	void HandleDestructionList();

	void Destroy(CEntity* InEntity);

	// Handling object collisions in the world
	void UpdateCollisions();
	void RegisterCollider(CCollider* Collider);
	void UnregisterCollider(CCollider* Collider);

	//Creating UniqueNames
	std::string GenerateUniqueEntityName(std::string Name);

	// Rendering Layers
	std::map<int, std::vector<CObject*>>& GetRenderLayers();
	void AddToRenderLayer(CObject* InObject);
	void RemoveFromRenderLayer(CObject* InObject);
};
