#include "CObject.h"
#include "CScript.h"
#include "CWorld.h"

using namespace std;

// CObject

CObject::CObject(CWorld* World) : CEntity(World)
{
	CreatesCollision = false;
	ReceivesCollision = false;
	Visible = true;
}

CObject::~CObject()
{
	if (GetWorld())
		GetWorld()->DestroyObject(this);
}

bool CObject::Created()
{
	if (GetWorld())
	{
		GetWorld()->AddObject(this);
		return 1;
	}

	return 0;
}


// Add Script
bool CObject::AddScript(CScript* Script, string NameOverride)
{
	if (!Script)
		return false;

	Script->SetOwner(this);

	if (NameOverride != "-")
		NameOverride = Script->GetEntityWorldID();

	Scripts[NameOverride] = Script;

	return true;
}

bool CObject::ExecuteScript(string ScriptName)
{
	if (Scripts.count(ScriptName) == 0)
		return false;

	Scripts[ScriptName]->Execute();
	return true;
}


// Rendering
bool CObject::IsVisible() { return Visible; }

void CObject::Render()
{

}


// Collision
void CObject::OnCollided(CObject* CollidingObject)
{

}

bool CObject::CheckCollisionWithAnotherObject(CObject* OtherObject)
{
	TVector2D LeftCorner = Position - (Collider.Size * 0.5f);
	TVector2D OtherLeftCorner = OtherObject->Position - (OtherObject->Collider.Size * 0.5f);
	
	bool OriginOverlapX = (LeftCorner.X < OtherLeftCorner.X) && (LeftCorner.X + Collider.Size.X > OtherLeftCorner.X);
	bool OriginOverlapY = (LeftCorner.Y < OtherLeftCorner.Y) && (LeftCorner.Y + Collider.Size.Y > OtherLeftCorner.Y);

	bool OtherOverlapX = (OtherLeftCorner.X < LeftCorner.X) && (OtherLeftCorner.X + OtherObject->Collider.Size.X > LeftCorner.X);
	bool OtherOverlapY = (OtherLeftCorner.Y < LeftCorner.Y) && (OtherLeftCorner.Y + OtherObject->Collider.Size.Y > LeftCorner.Y);


	return OriginOverlapX && OriginOverlapY || OtherOverlapX && OtherOverlapY;
}

void CObject::ReceivedCollision(CObject* CollidingObject)
{
	OnCollided(CollidingObject);
}

void CObject::CreatedCollision(CObject* CollidingObject)
{
	OnCollided(CollidingObject);
}


