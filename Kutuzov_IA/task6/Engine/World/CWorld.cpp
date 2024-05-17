#include "CWorld.h"
#include "CEntity.h"
#include "CObject.h"
#include "CScript.h"
#include "CWorldScriptHandler.h"

using namespace std;

// CWorld

CWorld::CWorld(CGame* InGame)
{
	if (InGame)
	{
		Game = InGame;

		WorldScriptHandler = Spawn<CWorldScriptHandler>("World Script Handler");
	}

	else
		throw (exception("Invalid Game pointer!"));
}

// Called every game frame
float CWorld::WorldUpdate(float DeltaTime)
{
	UpdateCollisions();

	// Calls update for every entity in the world
	for (auto Entity : Entities)
		Entity.second->EntityUpdate(DeltaTime);

	Update(DeltaTime);

	return 0.0f;
}

void CWorld::Update(float DetlaTime) {} // To override in child classes


// Returns Game Instance pointer
CGame* CWorld::GetGame() { return Game; }



// Spawning (for classes with defined CallSpawn)
template <typename T> T* CWorld::Spawn(std::string Name)
{
	T* NewObject = new T(this, Name);
	if (CallSpawn(NewObject))
		return NewObject;

	else
	{
		delete NewObject;
		return nullptr;
	}
}


// Entity handling
// Spawns entity into the world
bool CWorld::CallSpawn(CEntity* InEntity)
{
	int Index = 0;
	string EntityID = InEntity->EntityName;

	while (Entities.count(EntityID + "_" + to_string(Index)) > 0)
		Index++;

	EntityID += "_" + to_string(Index);
	Entities[EntityID] = InEntity;

	return InEntity->EntityCreated(EntityID, this);
}

// Adds a new object into the world
bool CWorld::CallSpawn(CObject* InObject)
{
	if (!InObject)
		return false;

	return CallSpawn(static_cast<CEntity*>(InObject)); // Spawns Entity
}

// Used for spawning world scripts
bool CWorld::CallSpawn(CScript* InScript)
{
	if (!InScript)
		return false;
	
	if (WorldScriptHandler)
		WorldScriptHandler->CallAddScript(InScript, InScript->EntityName);

	return true;
}



// Destroys entity in the world
bool CWorld::Destroy(CEntity* InEntity)
{
	if (!InEntity)
		return false;

	string EntityID = InEntity->GetEntityWorldID();

	if (!(Entities.count(EntityID) > 0))
		return false;

	Entities.erase(EntityID);
	delete InEntity;

	return true;
}

// Destroys object in the world
bool CWorld::Destroy(CObject* InObject)
{
	if (!InObject)
		return false;

	if (!(Entities.count(InObject->GetEntityWorldID()) > 0))
		return false;

	return Destroy(static_cast<CEntity*>(InObject));
}


// Handling object collisions in the world
void CWorld::UpdateCollisions()
{
	// Very unoptimized, should probably implement some kind of chunk system to handle this properly

	for (auto Collider : CollisionCreators)
		for (auto OtherCollider : CollisionReceivers)
			if (Collider.second->CheckCollision(OtherCollider.second))
			{
				Collider.second->GetOwner()->CreatedCollision(OtherCollider.second, Collider.second);
				OtherCollider.second->GetOwner()->ReceivedCollision(Collider.second, OtherCollider.second);
			}
}

void CWorld::RegisterCollider(CCollider* Collider)
{
	if (Collider->CreatesCollision)
		CollisionCreators[Collider->GetEntityWorldID()] = Collider;

	if (Collider->ReceivesCollision)
		CollisionReceivers[Collider->GetEntityWorldID()] = Collider;
}

void CWorld::UnregisterCollider(CCollider* Collider)
{
	if (Collider->CreatesCollision)
		CollisionCreators.erase(Collider->GetEntityWorldID());

	if (Collider->ReceivesCollision)
		CollisionReceivers.erase(Collider->GetEntityWorldID());
}


