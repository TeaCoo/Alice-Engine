#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
out vec4 pos;

void main()
{
	gl_Position = position;
	pos = position;
	v_TexCoord = texCoord;
}
