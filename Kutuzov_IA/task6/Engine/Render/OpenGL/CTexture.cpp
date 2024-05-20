#include "CTexture.h"
#include "../../Libs/stb_image.h"
#include <iostream>

CTexture::CTexture(const std::string& InFilePath) 
	: RendererID(0), FilePath(InFilePath), LocalBuffer(nullptr), Width(0), Height(0), BitsPerPixel(0)
{
	// To load pngs
	stbi_set_flip_vertically_on_load(1);
	LocalBuffer = stbi_load(InFilePath.c_str(), &Width, &Height, &BitsPerPixel, 4);

	GLCall(glGenTextures(1, &RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, RendererID));

	// Parameters
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	// Giving OpenGL data
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocalBuffer));
	UnBind();

	if (LocalBuffer)
		stbi_image_free(LocalBuffer);
}

CTexture::~CTexture()
{
	GLCall(glDeleteTextures(1, &RendererID));
}

void CTexture::Bind(unsigned int Slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + Slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, RendererID));
}

void CTexture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

int CTexture::GetWidth() const { return Width; }

int CTexture::GetHeight() const { return Height; }
