#include "CEntity.h"
#include "CWorld.h"
#include "../Game/CGame.h"

using namespace std;

// CEntity

CEntity::CEntity(CWorld* InWorld, std::string Name)
{
	if (InWorld)
		World = InWorld;

	EntityName = Name;
}

CEntity::~CEntity() {}

// Returns world pointer
CWorld* CEntity::GetWorld() { return World; }

// Returns ID in the world
string CEntity::GetEntityWorldID() { return EntityWorldID; }

// Returns Game Instance pointer
CGame* CEntity::GetGame() { return GetWorld()->GetGame(); }


// Called when entity is spawned into the game
bool CEntity::EntityCreated(string WorldID, CWorld* WorldOverride)
{
	EntityWorldID = WorldID;

	if (WorldOverride)
		World = WorldOverride;

	return Created();
}

bool CEntity::Created() { return true; } // To override in child classes


// Called every game frame
void CEntity::EntityUpdate(float DeltaTime)
{
	Update(DeltaTime);
}

void CEntity::Update(float DeltaTime) {} // To override in child classes


// Tags
void CEntity::AddTag(string& Tag)
{
	Tags.push_back(Tag);
}

bool CEntity::HasTag(string& Tag)
{
	for (string tag : Tags)
		if (tag == Tag)
			return true;

	return false;
}
