#shader Vertex
#version 330 core

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

out vec2 v_TexCoord;

void main()
{
   gl_Position = Position;
   v_TexCoord = TexCoord;
};


#shader Fragment
#version 330 core

layout(location = 0) out vec4 Color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 TexColor = texture(u_Texture, v_TexCoord);
	Color = TexColor;
};