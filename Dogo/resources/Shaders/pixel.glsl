#version 450 core

layout(location = 0) out vec4 color;
in vec3 v_Position;
in vec3 v_Color;
in vec2 v_Texture;

uniform sampler2D ourTexture;
uniform vec3 lightColor;
//uniform sampler2D ourTexture1;
void main()
{
	//color = mix(texture(ourTexture, v_Texture), texture(ourTexture1, v_Texture), 0.2);
	//color = texture(ourTexture, v_Texture);
	//color = vec4(1.0, 1.0, 1.0, 1.0);
	color = vec4(lightColor * v_Color, 1.0);
}