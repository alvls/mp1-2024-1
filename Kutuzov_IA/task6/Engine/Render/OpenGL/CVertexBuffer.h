#pragma once

class CVertexBuffer
{
private:
	unsigned int RendererID;

public:
	CVertexBuffer();
	CVertexBuffer(const void* Data, unsigned int Size);
	~CVertexBuffer();

	void SetData(const void* Data, unsigned int Size);

	void Bind() const;
	void UnBind() const;
};