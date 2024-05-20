#include "CIndexBuffer.h"
#include "DefOpenGL.h"

CIndexBuffer::CIndexBuffer()
{
	RendererID = 0;
	GLCall(glGenBuffers(1, &RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID));
}

CIndexBuffer::CIndexBuffer(const unsigned int* Data, unsigned int InCount) : Count(InCount)
{
	RendererID = 0;
	GLCall(glGenBuffers(1, &RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(GLuint), Data, GL_DYNAMIC_DRAW));
}

CIndexBuffer::~CIndexBuffer()
{
	GLCall(glDeleteBuffers(1, &RendererID));
}

void CIndexBuffer::SetData(const unsigned int* Data, unsigned int InCount)
{
	Bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(GLuint), Data, GL_DYNAMIC_DRAW));
}

void CIndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID));
}

void CIndexBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int CIndexBuffer::GetCount() { return Count; }
