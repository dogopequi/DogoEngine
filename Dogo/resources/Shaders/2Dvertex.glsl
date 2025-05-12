#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec3 a_Normal;
layout(location = 4) in float a_TexIndex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 v_Position;
out vec2 v_TexCoord;
out vec4 v_Color;
out vec3 v_Normal;
out float v_TexIndex;

void main()
{
	v_Color = a_Color;
	v_Position = a_Position;
	v_TexCoord = a_TexCoord;
    v_TexIndex = a_TexIndex;
    v_Normal = a_Normal;
	gl_Position = projection * view * model * vec4(a_Position, 1.0);
}