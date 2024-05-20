#pragma once

#include "DefOpenGL.h"
#include "CVertexArray.h"
#include "CIndexBuffer.h"
#include "CShader.h"

class CRenderer
{
public:
	void Draw(CVertexArray* VertexArray, CIndexBuffer* IndexBuffer, CShader* Shader) const;
};