#pragma once
#include "DefOpenGL.h"

#include <string>

class CTexture
{
	unsigned int RendererID;
	std::string FilePath;
	unsigned char* LocalBuffer;
	int Width, Height, BitsPerPixel;

public:
	CTexture(const std::string& InFilePath);
	~CTexture();

	void Bind(unsigned int Slot = 0) const;
	void UnBind() const;

	int GetWidth() const;
	int GetHeight() const;
};