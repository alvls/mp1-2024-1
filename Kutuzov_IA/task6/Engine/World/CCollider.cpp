#include "CCollider.h"
#include "CObject.h"

// Collider

CCollider::CCollider(CObject* Owner, std::string Name, TVector2D& In_RelativePosition) : CScript(Owner, Name)
{
	SetRelativePosition(In_RelativePosition);

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



// Rectange Collider

CRectangeCollider::CRectangeCollider(CObject* Owner, std::string Name, TVector2D& In_RelativePosition, TVector2D In_Size): CCollider(Owner, Name, In_RelativePosition)
{
	SetSize(In_Size);
}

// Collision Check
bool CRectangeCollider::CheckCollision(CCollider* OtherCollider)
{
	CRectangeCollider* RectCollider = static_cast<CRectangeCollider*>(OtherCollider);
	if (RectCollider)
		return CallCheckCollision(RectCollider);

	// Can add more other colliders here

	else
		return false;
}

bool CRectangeCollider::CallCheckCollision(CRectangeCollider* Collider)
{
	TVector2D LeftCorner = GetGlobalPosition() - (GetSize() * 0.5f);
	TVector2D OtherLeftCorner = Collider->GetGlobalPosition() - (Collider->GetSize() * 0.5f);

	bool OriginOverlapX = (LeftCorner.X < OtherLeftCorner.X) && (LeftCorner.X + GetSize().X > OtherLeftCorner.X);
	bool OriginOverlapY = (LeftCorner.Y < OtherLeftCorner.Y) && (LeftCorner.Y + GetSize().Y > OtherLeftCorner.Y);

	bool OtherOverlapX = (OtherLeftCorner.X < LeftCorner.X) && (OtherLeftCorner.X + Collider->GetSize().X > LeftCorner.X);
	bool OtherOverlapY = (OtherLeftCorner.Y < LeftCorner.Y) && (OtherLeftCorner.Y + Collider->GetSize().Y > LeftCorner.Y);


	return OriginOverlapX && OriginOverlapY || OtherOverlapX && OtherOverlapY;
}

bool CRectangeCollider::CallCheckCollision(CCollider* Collider)
{
	return false;
}

// Size
TVector2D CRectangeCollider::GetSize() { return Size; }

void CRectangeCollider::SetSize(TVector2D& In_Size) { Size = In_Size; }


