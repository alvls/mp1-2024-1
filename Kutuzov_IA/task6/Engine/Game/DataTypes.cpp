#include "DataTypes.h"
#include <cmath>

using namespace std;


// Vector 2D

TVector2D::TVector2D(float X_, float Y_): X(X_), Y(Y_) {}


float TVector2D::Length()
{
	return sqrt(X * X + Y * Y);
}

bool TVector2D::operator==(const TVector2D& InVector)
{
	return (X == InVector.X && Y == InVector.Y);
}

bool TVector2D::operator!=(const TVector2D& InVector)
{
	return (X != InVector.X || Y != InVector.Y);
}

TVector2D TVector2D::operator+(const TVector2D& InVector)
{
	return TVector2D(X + InVector.X, Y + InVector.Y);
}

TVector2D& TVector2D::operator+=(const TVector2D& InVector)
{
	X += InVector.X;
	Y += InVector.Y;

	return *this;
}


TVector2D TVector2D::operator-(const TVector2D& InVector)
{
	return TVector2D(X - InVector.X, Y - InVector.Y);
}

TVector2D& TVector2D::operator-=(const TVector2D& InVector)
{
	X -= InVector.X;
	Y -= InVector.Y;

	return *this;
}


TVector2D TVector2D::operator*(const float Scale)
{
	return TVector2D(X * Scale, Y * Scale);
}

TVector2D& TVector2D::operator*=(const float Scale)
{
	X *= Scale;
	Y *= Scale;

	return *this;
}


TVector2D TVector2D::operator*(const TVector2D& InVector)
{
	return TVector2D(X * InVector.X, Y * InVector.Y);
}

TVector2D& TVector2D::operator*=(const TVector2D& InVector)
{
	X *= InVector.X;
	Y *= InVector.Y;

	return *this;
}


TVector2D TVector2D::operator/(const float Scale)
{
	return TVector2D(X / Scale, Y / Scale);
}

TVector2D& TVector2D::operator/=(const float Scale)
{
	X /= Scale;
	Y /= Scale;

	return *this;
}


TVector2D TVector2D::operator/(const TVector2D& InVector)
{
	return TVector2D(X / InVector.X, Y / InVector.Y);
}

TVector2D& TVector2D::operator/=(const TVector2D& InVector)
{
	X /= InVector.X;
	Y /= InVector.Y;

	return *this;
}


TVector2D TVector2D::Normalize()
{
	float Len = Length();
	if (Len != 0.f)
		return *this / Len;

	return *this;
}

float TVector2D::DotProduct(TVector2D& InVector)
{
	return (X * InVector.X + Y * InVector.Y) / (Length() * InVector.Length());
}


// Sprite
TSprite::TSprite(std::string InSpriteID, TVector2D InRelPosition, float InScale): SpriteID(InSpriteID), RelPosition(InRelPosition), Scale(InScale) {}


// Camera

TVector2D TCamera::GetScreenSizeInUnits()
{
	return Resolution * UnitsPerPixel;
}


