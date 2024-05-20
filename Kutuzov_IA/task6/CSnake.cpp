#include "CSnake.h"
#include <iostream>
#include <cmath>

CSnakeHead::CSnakeHead(CWorld* InWorld, std::string InName) : CObject(InWorld, InName), CInputReceiver(InWorld->GetGame(), "SnakeInputReceiver")
{
	RenderLayerLocation.RenderLayer = 1;
	Sprites.push_back(TSprite("SnakeHead_F"));
	CurrentDirection = TVector2D(0.f, 1.f);
	InputDirection = TVector2D(0.f, 1.f);

	SetReceiveInput(true);

	Speed = 300.f;
	DistanceSinceLastCheck = 0.f;

	MouthCollider = AddScript<CRectangleCollider>("MouthCollider");
	MouthCollider->SetSize(TVector2D(80, 80));

	AddSegment();
	AddSegment();
	AddSegment();

	AddTag("Eater");
}



void CSnakeHead::ReceiveInput(int Input, char Action)
{
	if (Action == A_KEY_PRESS)
	{
		if (Input == KEY_UP || Input == KEY_W)
			SetInputDirection(TVector2D(0.f, 1.f));

		else if (Input == KEY_DOWN || Input == KEY_S)
			SetInputDirection(TVector2D(0.f, -1.f));

		else if (Input == KEY_LEFT || Input == KEY_A)
			SetInputDirection(TVector2D(-1.f, 0.f));

		else if (Input == KEY_RIGHT || Input == KEY_D)
			SetInputDirection(TVector2D(1.f, 0.f));
	}
}

bool CSnakeHead::Created()
{
	return true;
}

void CSnakeHead::Update(float DeltaTime)
{
	Move(CurrentDirection * DeltaTime * Speed);
	DistanceSinceLastCheck += DeltaTime * Speed;

	if (CurrentDirection.X != 0.f)
		SetPosition(TVector2D(GetPosition().X, TILE_SIZE * (int(GetPosition().Y) / TILE_SIZE)));

	if (CurrentDirection.Y != 0.f)
		SetPosition(TVector2D(TILE_SIZE * (int(GetPosition().X) / TILE_SIZE), GetPosition().Y));

	// UpdateBody;
	for (auto BodySegment : BodyList)
		BodySegment->Move(BodySegment->Direction * DeltaTime * Speed);

	if (DistanceSinceLastCheck >= TILE_SIZE)
	{
		for (int i = BodyList.size() - 1; i > 0; i--)
		{
			//BodyList[i]->Direction = BodyList[i]->NextDirection;
			BodyList[i]->Direction = BodyList[i - 1]->Direction;
		}

		BodyList[0]->Direction = CurrentDirection;
		

		DistanceSinceLastCheck = 0;
		CurrentDirection = InputDirection;
		UpdateSprite();
	}	
}

void CSnakeHead::SetInputDirection(TVector2D& NewDirection)
{
	if (NewDirection != CurrentDirection * -1.f)
		InputDirection = NewDirection;
}

void CSnakeHead::UpdateSprite()
{
	if (CurrentDirection.X == 1.f)
		Sprites[0].SpriteID = "SnakeHead_R";

	else if (CurrentDirection.X == -1.f)
		Sprites[0].SpriteID = "SnakeHead_L";

	else if (CurrentDirection.Y == 1.f)
		Sprites[0].SpriteID = "SnakeHead_F";

	else if (CurrentDirection.Y == -1.f)
		Sprites[0].SpriteID = "SnakeHead_B";
}

void CSnakeHead::GameOver()
{
	CSnakeWorld* SnakeWorldCast = static_cast<CSnakeWorld*>(GetWorld());
	if (SnakeWorldCast)
		SnakeWorldCast->GameOver();
}

void CSnakeHead::AddSegment()
{
	CSnakeBody* NewSegment = GetWorld()->Spawn<CSnakeBody>("SnakeBodySegment");
	int BodySize = BodyList.size();

	NewSegment->SpawnBody(this, BodySize);

	if (BodySize > 0)
	{
		NewSegment->Direction = BodyList[BodySize - 1]->Direction;
		NewSegment->SetPosition(BodyList[BodySize - 1]->GetPosition() - (BodyList[BodySize - 1]->Direction * TILE_SIZE));
	}

	else
	{
		NewSegment->Direction = CurrentDirection;
		NewSegment->SetPosition(GetPosition() - CurrentDirection * TILE_SIZE);
	}
	
	NewSegment->NextDirection = NewSegment->Direction;
	BodyList.push_back(NewSegment);
}


// Snake Body

CSnakeBody::CSnakeBody(CWorld* InWorld, std::string InName) : CObject(InWorld, InName) 
{
	Sprites.push_back(TSprite("SnakeBody"));
	SnakeHead = nullptr; 

	BodyCollider = AddScript<CRectangleCollider>("BodyCollider");
	BodyCollider->SetSize(TVector2D(80, 80));
}

void CSnakeBody::SpawnBody(CSnakeHead* InSnakeHead, int InIndex)
{
	SnakeHead = InSnakeHead;
	Index = InIndex;
}

void CSnakeBody::Update(float DeltaTime)
{
	if (Direction.X != 0.f)
		SetPosition(TVector2D(GetPosition().X, TILE_SIZE * (int(GetPosition().Y) / TILE_SIZE)));

	if (Direction.Y != 0.f)
		SetPosition(TVector2D(TILE_SIZE * (int(GetPosition().X) / TILE_SIZE), GetPosition().Y));

}

void CSnakeBody::OnCollided(CCollider* OtherCollider, CCollider* Collider)
{
	if (Index > 1 && OtherCollider->GetOwner() == SnakeHead)
		SnakeHead->GameOver();
}
