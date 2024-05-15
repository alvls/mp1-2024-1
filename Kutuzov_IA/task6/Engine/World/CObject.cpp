#include "CObject.h"
#include "CScript.h"
#include "CWorld.h"

using namespace std;

// CObject

CObject::CObject(CWorld* World, std::string Name) : CEntity(World, Name)
{
	Visible = true;
}

CObject::~CObject()
{
	for (auto Script : Scripts)
		delete Script.second;

	if (GetWorld())
		GetWorld()->Destroy(this);
}


// Position
TVector2D CObject::GetPosition() { return Position; }

void CObject::SetPosition(TVector2D& NewPosition) { Position = NewPosition; }

void CObject::Move(TVector2D& Offset) { Position += Offset; }


// Add Script
bool CObject::AddScript(CScript* Script, string Name)
{
	if (!Script)
		return false;

	string ScriptName = Name;
	int ScriptNameIndex = Scripts.count(Name);

	if (ScriptNameIndex > 0)
		ScriptName += to_string(ScriptNameIndex);

	Scripts[ScriptName] = Script;
	Script->EntityCreated(ScriptName);

	return true;
}


// Rendering
bool CObject::IsVisible() { return Visible; }


// Collision
void CObject::OnCollided(CObject* CollidingObject)
{

}

bool CObject::CheckCollisionWithAnotherObject(CObject* OtherObject)
{
	
}

void CObject::ReceivedCollision(CObject* CollidingObject)
{
	OnCollided(CollidingObject);
}

void CObject::CreatedCollision(CObject* CollidingObject)
{
	OnCollided(CollidingObject);
}



template<typename T> T* CObject::AddCollider(std::string ColliderName)
{
	T* NewCollider = GetWorld()->Spawn<T>(ColliderName);
	CallAddCollider()
}


void CObject::CallAddCollider(CCollider* Collider)
{
}
