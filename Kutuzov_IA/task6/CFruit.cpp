#include "CFruit.h"
#include "CSnakeWorld.h"
#include <iostream>

CFruit::CFruit(CWorld* World, std::string Name) : CObject(World, Name)
{
	MainCollider = AddScript<CRectangleCollider>("MainFruitCollider");
	MainCollider->SetSize(TVector2D(80, 80));

	Sprites.push_back(TSprite("Fruit"));
	RenderLayerLocation.RenderLayer = 1;
}

void CFruit::OnCollided(CCollider* OtherCollider, CCollider* Collider)
{
	if (OtherCollider->GetOwner()->HasTag("Eater"))
	{
		CSnakeWorld* SnakeWorldCast = dynamic_cast<CSnakeWorld*>(GetWorld());
		if (SnakeWorldCast)
			SnakeWorldCast->FruitEaten();

		GetWorld()->Destroy(this);
	}
}
