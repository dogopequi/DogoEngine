#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 v_Position;
out vec3 v_Normal;
out vec3 v_FragPosition;

void main()
{
	v_Position = a_Position;
    v_Normal = mat3(transpose(inverse(model))) * a_Normal;  
    v_FragPosition =  vec3(model * vec4(a_Position, 1.0));


	gl_Position = projection * view * model * vec4(a_Position, 1.0);
}