#include "CRenderOpenGL.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

CRenderOpenGL::CRenderOpenGL(CGame* InGame): CGameRender(InGame) 
{
    // Initialize the library
    if (!glfwInit())
        throw ("GLFW failed to intialize");

    // Create a windowed mode window and its OpenGL context
    Window = glfwCreateWindow(1920, 1080, InGame->GetGameName().c_str(), NULL, NULL);
    if (!Window)
    {
        glfwTerminate();
        throw ("GLFW failed to create a window");
    }

    // Make the window's context current
    glfwMakeContextCurrent(Window);

    if (glewInit() != GLEW_OK)
        throw ("GLEW isn't ok");

    InitRender();
}

CRenderOpenGL::~CRenderOpenGL()
{
    glDeleteProgram(Shader);
    glfwTerminate();
}



unsigned int CRenderOpenGL::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
{
    unsigned int Program = glCreateProgram();
    unsigned int Vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
    unsigned int Fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

    glAttachShader(Program, Vs);
    glAttachShader(Program, Fs);
    glLinkProgram(Program);
    glValidateProgram(Program);

    glDeleteShader(Vs);
    glDeleteShader(Fs);

    return Program;
}

unsigned int CRenderOpenGL::CompileShader(unsigned int Type, const std::string& Source)
{
    unsigned int ID = glCreateShader(Type);
    const char* Src = Source.c_str();
    glShaderSource(ID, 1, &Src, nullptr);
    glCompileShader(ID);

    // Check syntax errors
    int Result;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &Result);
    if (Result == GL_FALSE)
    {
        int Length;
        glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &Length);
        char* Message = (char*)alloca(Length * sizeof(char));
        glGetShaderInfoLog(ID, Length, &Length, Message);

        cout << "Failed to compile Shader" << (Type == GL_VERTEX_SHADER ? "Vertex: " : "Fragment: ") << endl << Message << endl;

        glDeleteShader(ID);
        return 0;
    }

    return ID;
}

void CRenderOpenGL::ParseShader(const string FilePath, string& OutVertexShader, string& OutFragmentShader)
{
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ifstream File(FilePath);

    if (File.is_open())
    {
        ShaderType Type = ShaderType::NONE;
        stringstream SStreams[2];

        string Line;
        while (getline(File, Line))
        {
            if (Line.find("#shader") != string::npos)
            {
                if (Line.find("Vertex") != string::npos)
                    Type = ShaderType::VERTEX;

                else if (Line.find("Fragment") != string::npos)
                    Type = ShaderType::FRAGMENT;
            }

            else
            {
                SStreams[(int)Type] << Line << "\n";
            }
        }

        OutVertexShader = SStreams[0].str();
        OutFragmentShader = SStreams[1].str();

        File.close();
    }  
}

void CRenderOpenGL::InitRender()
{
    float Positions[] =
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int Indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    glGenBuffers(1, &Buffer);
    glBindBuffer(GL_ARRAY_BUFFER, Buffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), Positions, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), Indices, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    string VertexShader, FragmentShader;

    ParseShader("Engine/Render/Shaders/Basic.shader", VertexShader, FragmentShader);

    Shader = CreateShader(VertexShader, FragmentShader);
    glUseProgram(Shader);
}

void CRenderOpenGL::RenderFrame()
{
    // Render here
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    // Swap front and back buffers
    glfwSwapBuffers(Window);

    // Poll for and process events
    glfwPollEvents();

    if (glfwWindowShouldClose(Window))
        Game->QuitGame();
}
