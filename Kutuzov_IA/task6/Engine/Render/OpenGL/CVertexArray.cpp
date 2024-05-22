#include "CVertexArray.h"
#include "DefOpenGL.h"

CVertexArray::CVertexArray()
{
	GLCall(glGenVertexArrays(1, &RendererID));
}

CVertexArray::~CVertexArray()
{
	GLCall(glDeleteVertexArrays(1, &RendererID));
}

void CVertexArray::AddBuffer(const CVertexBuffer& VertexBuffer, const CVertexBufferLayout& Layout)
{
	Bind();
	VertexBuffer.Bind();

	const auto& Elements = Layout.GetElements();
	unsigned int Offset = 0;
	
	for (unsigned int i = 0; i < Elements.size(); i++)
	{
		const auto& Elem = Elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, Elem.Count, Elem.Type,
			Elem.Normalized ? GL_TRUE : GL_FALSE, Layout.GetStride(), (const void*)Offset));

		Offset += Elem.Count * TVertexBufferElement::GetSizeOfType(Elem.Type);
	}
}

void CVertexArray::Bind() const
{
	GLCall(glBindVertexArray(RendererID));
}

void CVertexArray::UnBind() const
{
	GLCall(glBindVertexArray(0));
}
