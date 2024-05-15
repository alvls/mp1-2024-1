#include "CWorld.h"
#include "CEntity.h"
#include "CObject.h"

using namespace std;

// CWorld

CWorld::CWorld(CGame* InGame)
{
	if (InGame)
		Game = InGame;

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

	return nullptr;
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

	if (InObject->ReceivesCollision)
		CollisionReceivers.push_back(InObject);

	if (InObject->CreatesCollision)
		CollisionCreators.push_back(InObject);

	CallSpawn(static_cast<CEntity*>(InObject)); // Spawns Entity
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

	if (InObject->ReceivesCollision)
		CollisionReceivers.erase(remove(CollisionReceivers.begin(), CollisionReceivers.end(), InObject), CollisionReceivers.end());

	if (InObject->CreatesCollision)
		CollisionCreators.erase(remove(CollisionCreators.begin(), CollisionCreators.end(), InObject), CollisionCreators.end());

	return Destroy(static_cast<CEntity*>(InObject));
}


// Handling object collisions in the world
void CWorld::UpdateCollisions()
{

	// Very unoptimized, should probably implement some kind of chunk system to handle this properly

	for (auto Object : CollisionCreators)
		for (auto OtherObject : CollisionReceivers)
			if (Object->CheckCollisionWithAnotherObject(OtherObject))
			{
				Object->CreatedCollision(OtherObject);
				OtherObject->ReceivedCollision(Object);
			}
}


