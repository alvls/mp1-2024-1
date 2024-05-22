#include "CVertexBuffer.h"
#include "DefOpenGL.h"

CVertexBuffer::CVertexBuffer()
{
	RendererID = 0;
	GLCall(glGenBuffers(1, &RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, RendererID));
}

CVertexBuffer::CVertexBuffer(const void* Data, unsigned int Size)
{
	RendererID = 0;
	GLCall(glGenBuffers(1, &RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_DYNAMIC_DRAW));
}

CVertexBuffer::~CVertexBuffer()
{
	GLCall(glDeleteBuffers(1, &RendererID));
}

void CVertexBuffer::SetData(const void* Data, unsigned int Size)
{
	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_DYNAMIC_DRAW));
}

void CVertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, RendererID));
}

void CVertexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
