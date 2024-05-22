#include "CRenderOpenGL.h"
#include "../World/CWorld.h"
#include "../World/CObject.h"
#include "../Game/CGame.h"
#include "../Game/CPlayerController.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "OpenGL/DefOpenGL.h"
#include "OpenGL/CVertexBuffer.h"
#include "OpenGL/CIndexBuffer.h"
#include "OpenGL/CVertexArray.h"
#include "OpenGL/CShader.h"
#include "OpenGL/CRenderer.h"
#include "OpenGL/CTexture.h"

using namespace std;


// Sprite
TSpriteGL::TSpriteGL() 
{
    Size = TVector2D();
}

TSpriteGL::TSpriteGL(std::string InTextureFilePath, TVector2D InSize): TextureFilePath(InTextureFilePath), Size(InSize){}

TSpriteGL::TSpriteGL(std::string InTextureFilePath, float InSizeX, float InSizeY)
    : TextureFilePath(InTextureFilePath)
{
    Size.X = InSizeX;
    Size.Y = InSizeY;
}


// Input Receiving
CGame* GlobalGamePtr;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
        GlobalGamePtr->GetPlayerController()->SendInput(key, A_KEY_PRESS);

    else if (action == GLFW_RELEASE)
        GlobalGamePtr->GetPlayerController()->SendInput(key, A_KEY_RELEASE);
}


// Render Open GL
CRenderOpenGL::CRenderOpenGL(CGame* InGame, map<string, TSpriteGL> InSpritePool): CGameRender(InGame)
{
    GlobalGamePtr = InGame;

    // Initialize the library
    if (!glfwInit())
        throw ("GLFW failed to intialize");

    // Create a windowed mode window and its OpenGL context
    Window = glfwCreateWindow(InGame->GetCamera().Resolution.X, InGame->GetCamera().Resolution.Y, InGame->GetGameName().c_str(), NULL, NULL);
    if (!Window)
    {
        glfwTerminate();
        throw ("GLFW failed to create a window");
    } 

    // Make the window's context current
    glfwMakeContextCurrent(Window);

    if (glewInit() != GLEW_OK)
        throw ("GLEW isn't ok");

    glfwSetKeyCallback(Window, &KeyCallback);
    GLFWkeyfun;

    SpritePool = InSpritePool;
    for (auto Sprite : SpritePool)
    {
        CTexture* Texture = new CTexture(Sprite.second.TextureFilePath);
        Textures[Sprite.first] = Texture;
    }

    InitRender();
}

CRenderOpenGL::~CRenderOpenGL()
{
    delete VertexArray;
    delete VertexBuffer;
    delete IndexBuffer;
    delete Shader;
    delete WorldRenderer;

    for (auto Texture : Textures)
        delete Texture.second;

    glfwTerminate();
}


// Transformation
TVector2D CRenderOpenGL::WorldToScreenCoordinates(TVector2D& WorldPosition)
{
    return WorldPosition - Game->GetCamera().Position / (Game->GetCamera().GetScreenSizeInUnits() / 2.f);
}

float CRenderOpenGL::WorldToScreenCoordinatesAxisX(float X)
{
    return (X - Game->GetCamera().Position.X) / (Game->GetCamera().GetScreenSizeInUnits().X / 2.f);
}

float CRenderOpenGL::WorldToScreenCoordinatesAxisY(float Y)
{
    return (Y - Game->GetCamera().Position.Y) / (Game->GetCamera().GetScreenSizeInUnits().Y / 2.f);
}


void CRenderOpenGL::InitRender()
{
    unsigned int Indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    
    WorldRenderer = new CRenderer();

    VertexArray = new CVertexArray();
    VertexBuffer = new CVertexBuffer();

    CVertexBufferLayout Layout;
    Layout.Push<float>(2);
    Layout.Push<float>(2);

    VertexArray->AddBuffer(*VertexBuffer, Layout);

    IndexBuffer = new CIndexBuffer(Indices, 6);

    Shader = new CShader("Engine/Render/Shaders/Basic.shader");

    VertexArray->UnBind();
    VertexBuffer->UnBind();
    IndexBuffer->UnBind();
    Shader->UnBind();
}

void CRenderOpenGL::RenderFrame()
{
    // Render here
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (auto RenderLayer : Game->GetWorld()->GetRenderLayers())
        for (auto Object : RenderLayer.second)
        if (Object->IsVisible())
            RenderObject(Object);

    // Swap front and back buffers
    glfwSwapBuffers(Window);

    // Poll for and process events
    glfwPollEvents();

    if (glfwWindowShouldClose(Window))
        Game->QuitGame();
}


// Rendering
void CRenderOpenGL::RenderObject(CObject* Object)
{
    for (auto Sprite : Object->GetSprites())
        RenderSprite(Sprite.SpriteID, Sprite.RelPosition + Object->GetPosition(), Sprite.TargetSize, Sprite.Scale);
}

void CRenderOpenGL::RenderSprite(string SpriteID, TVector2D WorldPosition, TVector2D TargetSize, float Scale)
{
    TSpriteGL& Sprite = SpritePool[SpriteID];

    TVector2D Sz = Sprite.Size * Scale * TargetSize;
    TVector2D Pos = WorldPosition;

    float Positions[] =
    {
         WTSX(-Sz.X / 2 + Pos.X), WTSY(-Sz.Y / 2 + Pos.Y), 0.f, 0.f,
         WTSX( Sz.X / 2 + Pos.X), WTSY(-Sz.Y / 2 + Pos.Y), 1.f, 0.f,
         WTSX( Sz.X / 2 + Pos.X), WTSY( Sz.Y / 2 + Pos.Y), 1.f, 1.f,
         WTSX(-Sz.X / 2 + Pos.X), WTSY( Sz.Y / 2 + Pos.Y), 0.f, 1.f
    };

    VertexBuffer->SetData(Positions, 4 * 4 * sizeof(float));

    Textures[SpriteID]->Bind();
    Shader->SetUniform1i("u_Texture", 0);

    //Shader->SetUniform4f("u_Color", abs(WTSX(Pos.X)), 1 - abs(WTSY(Pos.Y)), 1.f, 1.f);

    WorldRenderer->Draw(VertexArray, IndexBuffer, Shader);
   
}