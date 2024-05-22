#include "CVertexBufferLayout.h"
#include "DefOpenGL.h"

TVertexBufferElement::TVertexBufferElement(unsigned int InType, unsigned int InCount, bool InNormalized): 
	Type(InType), Count(InCount), Normalized(InNormalized) {}

unsigned int TVertexBufferElement::GetSizeOfType(unsigned int Type)
{
	switch (Type)
	{
	case GL_FLOAT:			return 4;
	case GL_UNSIGNED_INT:	return 4;
	case GL_UNSIGNED_BYTE:	return 1;
	}

	ASSERT(false);
	return 0;
}



CVertexBufferLayout::CVertexBufferLayout(): Stride(0)
{
}

const std::vector<TVertexBufferElement>& CVertexBufferLayout::GetElements() const
{
	return Elements;
}

unsigned int CVertexBufferLayout::GetStride() const
{
	return Stride;
}
