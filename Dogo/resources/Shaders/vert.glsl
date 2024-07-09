#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_Texture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform mat4 MVP;

out vec3 v_Position;
out vec3 v_Color;
out vec2 v_Texture;

void main()
{
	v_Color = a_Color;
	v_Position = a_Position;
	v_Texture = a_Texture;
	gl_Position = projection * view * model * vec4(a_Position, 1.0);
	//gl_Position = MVP * vec4(a_Position, 1.0);
}