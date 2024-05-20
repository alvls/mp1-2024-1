#pragma once
#include <vector>
#include <GL/glew.h>

struct TVertexBufferElement
{
	unsigned int Type;
	unsigned int Count;
	bool Normalized;

	TVertexBufferElement(unsigned int InType, unsigned int InCount, bool InNormalized);

	static unsigned int GetSizeOfType(unsigned int Type);
};

class CVertexBufferLayout
{
	std::vector<TVertexBufferElement> Elements;
	unsigned int Stride;

public:
	CVertexBufferLayout();

	template<typename T> void Push(unsigned int Count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int Count)
	{
		Elements.push_back(TVertexBufferElement(GL_FLOAT, Count, false));
		Stride += TVertexBufferElement::GetSizeOfType(GL_FLOAT) * Count;
	}

	template<>
	void Push<unsigned int>(unsigned int Count)
	{
		Elements.push_back(TVertexBufferElement(GL_UNSIGNED_INT, Count, false));
		Stride += TVertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * Count;
	}

	template<>
	void Push<unsigned char>(unsigned int Count)
	{
		Elements.push_back(TVertexBufferElement(GL_UNSIGNED_BYTE, Count, true));
		Stride += TVertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * Count;
	}

	const std::vector<TVertexBufferElement>& GetElements() const;
	unsigned int GetStride() const;
};