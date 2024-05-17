#shader Vertex
#version 330 core

layout(location = 0) in vec4 Position;

void main()
{
   gl_Position = Position;
};



#shader Fragment
#version 330 core

layout(location = 0) out vec4 Color;

void main()
{
   Color = vec4(1.0, 1.0, 0.0, 1.0);
};