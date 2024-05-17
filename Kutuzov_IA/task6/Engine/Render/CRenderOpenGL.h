#pragma once
#include "CGameRender.h"

struct GLFWwindow;


class CRenderOpenGL : public CGameRender
{
protected:
	//CWindow* Window;
	GLFWwindow* Window;
	
	unsigned int Buffer;
	unsigned int IndexBuffer;

	unsigned int Shader;

// Rendering override
	virtual void RenderFrame();

public:
	CRenderOpenGL(CGame* InGame);
	~CRenderOpenGL();

	// Shaders
	static unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);
	static unsigned int CompileShader(unsigned int Type, const std::string& Source);

	void static ParseShader(const std::string FilePath, std::string& OutVertexShader, std::string& OutFragmentShader);

	void InitRender();
};
