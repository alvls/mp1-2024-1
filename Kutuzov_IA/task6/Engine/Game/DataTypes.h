#pragma once
#include <map>

struct TVector2D
{
	float X, Y;

	TVector2D(float X_ = 0.f, float Y_ = 0.f);

	float Length();

	TVector2D operator+(TVector2D& InVector);
	TVector2D operator+=(TVector2D& InVector);

	TVector2D operator-(TVector2D& InVector);
	TVector2D operator-=(TVector2D& InVector);

	TVector2D operator*(float Scale);
	TVector2D operator*=(float Scale);

	TVector2D operator*(TVector2D& InVector);
	TVector2D operator*=(TVector2D& InVector);

	TVector2D operator/(float Scale);
	TVector2D operator/=(float Scale);

	TVector2D Normalize();
	float DotProduct(TVector2D& InVector);

};

struct TSprite
{
	TVector2D Size;
	std::map<TVector2D, char> Pixels;
};

struct TRectangleCollider
{
	TVector2D Size;
};
