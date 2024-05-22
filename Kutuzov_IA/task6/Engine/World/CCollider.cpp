#include "CCollider.h"
#include "CObject.h"
#include "CWorld.h"
#include <cmath>

using namespace std;

// Collider

CCollider::CCollider(CObject* Owner, std::string Name)
	: CScript(Owner, Name)
{
	SetRelativePosition(TVector2D());
	ReceivesCollision = true;
	CreatesCollision = true;
}

CCollider::~CCollider()
{
	UnRegisterCollider();
}

bool CCollider::Created()
{
	RegisterCollider();
	return true;
}

void CCollider::UpdateCollisionSettings(bool InReceivesCollision, bool InCreatesCollision)
{
	UnRegisterCollider();
	ReceivesCollision = InReceivesCollision;
	CreatesCollision = InCreatesCollision;
	RegisterCollider();
}

// Registering
bool CCollider::RegisterCollider()
{
	if (!Registered && GetOwner())
	{
		GetOwner()->GetWorld()->RegisterCollider(this);

		Registered = true;

		return true;
	}

	return false;
}

bool CCollider::UnRegisterCollider()
{
	if (Registered && GetOwner())
	{
		GetOwner()->GetWorld()->UnregisterCollider(this);

		Registered = false;

		return true;
	}

	return false;
}

// Checks if collisions happen
bool CCollider::CheckCollision(CCollider* OtherCollider)
{
	return false;
}

// Relative Position
TVector2D CCollider::GetRelativePosition() { return RelativePosition; }

// Sets the Relative Position
void CCollider::SetRelativePosition(TVector2D& In_RelativePosition) { RelativePosition = In_RelativePosition; }

TVector2D CCollider::GetGlobalPosition()
{
	return RelativePosition + Owner->GetPosition();
}

// Current Collisions
void CCollider::AddCollision(CCollider* Collider)
{
	CurrentCollisions[Collider->GetEntityWorldID()] = Collider;
}

void CCollider::RemoveCollision(CCollider* Collider)
{
	CurrentCollisions.erase(Collider->GetEntityWorldID());
}

bool CCollider::HasCollisionWith(CCollider* Collider)
{
	return (CurrentCollisions.find(Collider->GetEntityWorldID()) != CurrentCollisions.end());
}



// Rectange Collider

CRectangleCollider::CRectangleCollider(CObject* Owner, std::string Name) : CCollider(Owner, Name)
{
	SetSize(TVector2D());
}

// Collision Check
bool CRectangleCollider::CheckCollision(CCollider* OtherCollider)
{
	CRectangleCollider* RectCollider = static_cast<CRectangleCollider*>(OtherCollider);
	if (RectCollider)
		return CallCheckCollision(RectCollider);

	// Can add more other colliders here

	else
		return false;
}

bool CRectangleCollider::CallCheckCollision(CRectangleCollider* Collider)
{
	bool Collision = !( (Left() > Collider->Right()) || (Right() < Collider->Left()) || (Bottom() > Collider->Top()) || (Top() < Collider->Bottom()) );

	return Collision;
}

bool CRectangleCollider::CallCheckCollision(CCollider* Collider)
{
	return false;
}

// Size
TVector2D CRectangleCollider::GetSize() { return Size; }

void CRectangleCollider::SetSize(TVector2D& In_Size) { Size = In_Size; }

// Sides
float CRectangleCollider::Left()
{
	TVector2D GlobPos = GetGlobalPosition();
	return GlobPos.X - (Size.X / 2);
}

float CRectangleCollider::Right()
{
	TVector2D GlobPos = GetGlobalPosition();
	return GlobPos.X + (Size.X / 2);
}

float CRectangleCollider::Top()
{
	TVector2D GlobPos = GetGlobalPosition();
	return GlobPos.Y + (Size.Y / 2);
}

float CRectangleCollider::Bottom()
{
	TVector2D GlobPos = GetGlobalPosition();
	return GlobPos.Y - (Size.Y / 2);
}


