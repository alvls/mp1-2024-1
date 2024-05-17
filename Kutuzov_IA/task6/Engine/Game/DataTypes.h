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

struct TCamera
{
	TVector2D Position = TVector2D(0.f, 0.f);

	TVector2D Resolution = TVector2D(1280.f, 720.f);
	float UnitsPerPixel = 1.f;
};

