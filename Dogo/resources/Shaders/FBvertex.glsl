#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;

layout(location = 0) out vec3 v_Position;
layout(location = 1) out vec4 v_Color;
layout(location = 2) out vec2 v_TexCoord;
layout(location = 3) out flat float v_TexIndex;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	v_Position = a_Position;
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
    v_TexIndex = a_TexIndex;
	gl_Position = projection * view * vec4(a_Position, 1.0);
}