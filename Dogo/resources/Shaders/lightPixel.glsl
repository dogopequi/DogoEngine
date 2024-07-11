#version 450 core

layout(location = 0) out vec4 color;
in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;

void main()
{
	color = vec4(1.0, 1.0, 1.0, 1.0);
}