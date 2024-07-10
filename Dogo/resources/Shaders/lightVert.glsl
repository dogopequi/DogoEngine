#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform mat4 MVP;

out vec3 v_Position;
out vec3 v_Normal;

void main()
{
	v_Position = a_Position;
    v_Normal = a_Normal;
	gl_Position = projection * view * model * vec4(a_Position, 1.0);
	//gl_Position = MVP * vec4(a_Position, 1.0);
}