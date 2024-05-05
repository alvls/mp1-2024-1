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

// Entity handling
// Spawns entity into the world
bool CWorld::SpawnEntity(CEntity* InEntity)
{
	int Index = 0;
	string EntityID = InEntity->Name;

	while (Entities.count(EntityID + "_" + to_string(Index)) > 0)
		Index++;

	EntityID += "_" + to_string(Index);
	Entities[EntityID] = InEntity;

	return InEntity->EntityCreated(EntityID, this);
}

// Destroys entity in the world
bool CWorld::DestroyEntity(CEntity* InEntity)
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

// Adds a new object into the world
bool CWorld::AddObject(CObject* InObject)
{
	if (!InObject)
		return false;

	if (!(Entities.count(InObject->GetEntityWorldID()) > 0))
		return false;


	if (InObject->ReceivesCollision)
		CollisionReceivers.push_back(InObject);

	if (InObject->CreatesCollision)
		CollisionCreators.push_back(InObject);

	return true;
}

// Destroys object in the world
bool CWorld::DestroyObject(CObject* InObject)
{
	if (!InObject)
		return false;

	if (!(Entities.count(InObject->GetEntityWorldID()) > 0))
		return false;


	if (InObject->ReceivesCollision)
		CollisionReceivers.erase(remove(CollisionReceivers.begin(), CollisionReceivers.end(), InObject), CollisionReceivers.end());

	if (InObject->CreatesCollision)
		CollisionCreators.erase(remove(CollisionCreators.begin(), CollisionCreators.end(), InObject), CollisionCreators.end());

	return true;
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


