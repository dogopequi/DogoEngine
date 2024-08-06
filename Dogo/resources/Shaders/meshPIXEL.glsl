#version 450 core
layout(location = 0) out vec4 FragColor;

in vec3 v_Position;
in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_FragPosition;

uniform vec3 MeshColor;

void main()
{
	FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}