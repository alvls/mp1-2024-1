#pragma once

class CIndexBuffer
{
private:
	unsigned int RendererID;
	unsigned int Count;

public:
	CIndexBuffer();
	CIndexBuffer(const unsigned int* Data, unsigned int InCount);
	~CIndexBuffer();

	void SetData(const unsigned int* Data, unsigned int InCount);

	void Bind() const;
	void UnBind() const;

	unsigned int GetCount();
};