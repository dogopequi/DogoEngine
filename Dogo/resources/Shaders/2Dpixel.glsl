#version 450 core

layout(location = 0) out vec4 color;
layout(location = 1) in vec4 v_Color;
layout(location = 2) in vec2 v_TexCoord;
layout(location = 3) in flat float v_TexIndex;

uniform sampler2DArray textureArray;
void main()
{
   int layer = int(v_TexIndex);
   color = texture(textureArray, vec3(v_TexCoord, layer)) * v_Color;
}