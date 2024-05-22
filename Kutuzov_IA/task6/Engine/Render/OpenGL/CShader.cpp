#include "CShader.h"
#include "DefOpenGL.h"
#include <fstream>
#include <sstream>

using namespace std;

CShader::CShader(const std::string& InFilePath) : FilePath(InFilePath)
{
    string VertexShader, FragmentShader;
    ParseShader(InFilePath, VertexShader, FragmentShader);
    RendererID = CreateShader(VertexShader, FragmentShader);
}

CShader::~CShader()
{
    GLCall(glDeleteProgram(RendererID));
}

void CShader::Bind() const
{
    GLCall(glUseProgram(RendererID));
}

void CShader::UnBind() const
{
    GLCall(glUseProgram(0));
}

void CShader::SetUniform4f(const std::string& Name, float v0, float v1, float v2, float v3)
{
    Bind();
    GLCall(glUniform4f(GetUniformLocation(Name), v0, v1, v2, v3));
}

void CShader::SetUniform1i(const std::string& Name, int v)
{
    Bind();
    GLCall(glUniform1i(GetUniformLocation(Name), v));
}

unsigned int CShader::CompileShader(unsigned int Type, const std::string& Source)
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

int CShader::GetUniformLocation(const std::string& Name)
{
    if (UniformLocationCache.find(Name) != UniformLocationCache.end())
        return UniformLocationCache[Name];

    GLCall(int Location = glGetUniformLocation(RendererID, Name.c_str()));

    if (Location == -1)
        cout << "Warning: uniform '" << Name << "' Doesnt exist!";

    UniformLocationCache[Name] = Location;
    return Location;
}

unsigned int CShader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
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

void CShader::ParseShader(const string FilePath, string& OutVertexShader, string& OutFragmentShader)
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