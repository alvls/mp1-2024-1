#pragma once
#include "CVertexBuffer.h"
#include "CVertexBufferLayout.h"

class CVertexArray
{
private:
	unsigned int RendererID;

public:
	CVertexArray();
	~CVertexArray();

	void AddBuffer(const CVertexBuffer& VertexBuffer, const CVertexBufferLayout& Layout);

	void Bind() const;
	void UnBind() const;
};