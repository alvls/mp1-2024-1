#pragma once
#include "CGameRender.h"
#include "../Game/DataTypes.h"

#include <map>
#include <string>

#define WTS WorldToScreenCoordinates
#define WTSX WorldToScreenCoordinatesAxisX
#define WTSY WorldToScreenCoordinatesAxisY

struct GLFWwindow;
class CVertexBuffer;
class CIndexBuffer;
class CVertexArray;
class CShader;
class CRenderer;
class CTexture;
class CObject;

struct TSpriteGL
{
	std::string TextureFilePath;
	TVector2D Size;

	TSpriteGL();
	TSpriteGL(std::string InTextureFilePath, TVector2D InSize);
	TSpriteGL(std::string InTextureFilePath, float InSizeX, float InSizeY);
};


class CRenderOpenGL : public CGameRender
{
protected:

	// Sprite Pool
	std::map<std::string, TSpriteGL> SpritePool;
	std::map<std::string, CTexture*> Textures;

	GLFWwindow* Window;
	
	CVertexArray* VertexArray;
	CVertexBuffer* VertexBuffer;
	CIndexBuffer* IndexBuffer;
	CShader* Shader;
	CRenderer* WorldRenderer;

	// Rendering override
	virtual void RenderFrame();

public:
	CRenderOpenGL(CGame* InGame, std::map<std::string, TSpriteGL> InSpritePool);
	~CRenderOpenGL();

	// Transformation
	TVector2D WorldToScreenCoordinates(TVector2D& WorldPosition);
	float WorldToScreenCoordinatesAxisX(float X);
	float WorldToScreenCoordinatesAxisY(float Y);

	// Rendering
	void RenderObject(CObject* Object);
	void RenderSprite(std::string SpriteID, TVector2D WorldPosition, float Scale);

	void InitRender();
};
